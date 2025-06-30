#!/bin/bash

if [ $# -ne 2 ];
then
 echo $0: Not enough parameters.
 exit 1
fi

KERNELSRCDIR="$1"
CONFIG="$KERNELSRCDIR/.config"
MODULE="$2"

KERNEL_VER=$(uname -r | cut -d . -f 1)
KERNEL_MAJ=$(uname -r | cut -d . -f 2 | awk '{ printf("%02d\n", $1) }') 
KERNEL_MIN=$(uname -r | cut -d . -f 3 | awk '{ printf("%02d\n", $1) }')
KERNEL_REV=${KERNEL_VER}${KERNEL_MAJ}${KERNEL_MIN}


########################################################################
# Function to check if an option is set in the Kernel configuration file
########################################################################
# $1	Kernel config file path
# $2	Option string
########################################################################
function is_set ()
{
	[ -f "$1" ] && VALUE=$(grep "^$2=" "$1" | cut -f 2- -d "=")
	if [ "$VALUE" == "y" ]
	then
		return 0
	fi
	return 1
}

########################################################################
# Function to check if the certificate for signing does exist
########################################################################
# $1	Private key
# $2	Public key
########################################################################
function is_cert_ok ()
{
	if [ ! -f $1 ];
	then
		echo "No private key found: $1"
		return 1;
	fi

	if [ ! -f $2 ];
	then
		echo "No public key found: $2"
		return 1;
	fi

	return 0
}


########################################################################
# Function to generate a certificate for signing
########################################################################
# $1	Private key
# $2	Public key
########################################################################
function create_self_signed_cert ()
{
  echo -e "[ req ] \n\
	default_bits = 4096 \n\
	distinguished_name = req_distinguished_name\n\
	prompt = no\n\
	x509_extensions = myexts\n\
	\n\
	[ req_distinguished_name ]\n\
	CN = Modules\n\
	\n\
	[ myexts ] \n\
	basicConstraints=critical,CA:FALSE \n\
	keyUsage=digitalSignature \n\
	subjectKeyIdentifier=hash \n\
	authorityKeyIdentifier=keyid" > /tmp/x509.genkey

  echo "Creating a certificate..."
  openssl req -new -nodes -utf8 -sha512 -days 36500 -batch -x509 -config /tmp/x509.genkey -outform DER -keyout $1 -out $2
  RETVAL=$?

  rm /tmp/x509.genkey

  return $RETVAL
}

# Note: 40303 = 4.3.3
if [[ ${KERNEL_REV} -lt 40303 ]]
then
     is_set "$CONFIG" CONFIG_MODULE_SIG

     if [ $? -eq 0 ];
     then
     	PRIV_KEY=$KERNELSRCDIR/signing_key.priv
	PUB_KEY=$KERNELSRCDIR/signing_key.x509

        is_cert_ok $PRIV_KEY $PUB_KEY
        if [ $? -eq 1 ];
        then
                create_self_signed_cert $PRIV_KEY $PUB_KEY
        fi
        if [ $? -eq 0 ];
        then
                echo "Signing $MODULE..."
        	perl "$KERNELSRCDIR/scripts/sign-file" "sha512" "$PRIV_KEY" "$PUB_KEY" "$MODULE"
        fi
     fi
else
     is_set "$CONFIG" CONFIG_MODULE_SIG

     if [ $? -eq 0 ];
     then
     	PRIV_KEY=$KERNELSRCDIR/certs/signing_key.pem
	PUB_KEY=$KERNELSRCDIR/certs/signing_key.x509

	mkdir -p $KERNELSRCDIR/certs

     	is_cert_ok $PRIV_KEY $PUB_KEY
	if [ $? -eq 1 ];
	then
		create_self_signed_cert $PRIV_KEY $PUB_KEY
     	fi
	if [ $? -eq 0 ];
	then
		echo "Signing $MODULE..."
     		$KERNELSRCDIR/scripts/sign-file sha512 $PRIV_KEY $PUB_KEY $MODULE
     	fi
     fi
fi

exit 0
