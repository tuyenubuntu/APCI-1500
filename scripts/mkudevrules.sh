#!/bin/bash
# Test if ADDI-DATA udev rules exist, if not create them.

DRIVER_NAME=$1
CARD_GROUP="addi-data-cards"

UDEVRULEFILENAME=/etc/udev/addidata.rules
UDEVRULESYMLINK=/etc/udev/rules.d/addidata.rules

if [ ! -f "$UDEVRULEFILENAME" ];
then
        echo "File $UDEVRULEFILENAME does not exist - creating it."
        touch $UDEVRULEFILENAME
        echo "# Generated automatically by ADDI-DATA installation script" >> $UDEVRULEFILENAME
else
        echo "File $UDEVRULEFILENAME already exists."
fi;

if [ ! -L "$UDEVRULESYMLINK" ];
then
        ln -s $UDEVRULEFILENAME $UDEVRULESYMLINK
fi

COMEDI_DRIVER_LIST=$(find /usr/lib/modules/$(uname -r) -name "addi_apci*")

if [ -n "$COMEDI_DRIVER_LIST" ]; then
    echo "---------------------------------------------"
    echo "      /!\\ Blacklisting Comedi drivers,"
    echo "they are not compatible with official drivers"
    echo "---------------------------------------------"

    for card in $COMEDI_DRIVER_LIST; do
        filename=$(basename -- "$card")
        modulename="${filename%%.*}"
        if ! grep -q "^blacklist $modulename" /etc/modprobe.d/blacklist.conf; then
            echo "blacklist $modulename" >> /etc/modprobe.d/blacklist.conf
        fi
    done
    update-initramfs -u
else
    echo "No Comedi drivers found."
fi

TMPSTR=`grep "SUBSYSTEMS==\"$DRIVER_NAME\"" $UDEVRULEFILENAME`
echo "Creating group $CARD_GROUP if it does not exist"
getent group $CARD_GROUP || groupadd $CARD_GROUP
echo "----------------------------------"
echo "Please use the following command to add your user to the group $CARD_GROUP:"
echo "usermod -aG $CARD_GROUP \$USER"
echo "----------------------------------"
if [ "" == "$TMPSTR" ];
then
        echo Adding rule for $DRIVER_NAME to $UDEVRULEFILENAME
        echo "SUBSYSTEMS==\"$DRIVER_NAME\", SYMLINK+=\"$DRIVER_NAME/%m\", GROUP=\"$CARD_GROUP\", MODE=\"0660\"" >> $UDEVRULEFILENAME
        echo Reloading udev
	which udevcontrol >/dev/null 2>&1
		if [ $? -eq 0 ];
		then
			udevcontrol reload_rules
		else
			udevadm control --help | grep "reload_rules" && udevadm control --reload_rules || udevadm control --reload-rules
		fi;
else
        echo A rule for $DRIVER_NAME already exists in file $UDEVRULEFILENAME
fi;
