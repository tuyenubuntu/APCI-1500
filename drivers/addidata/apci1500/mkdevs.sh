#!/bin/bash

# Load the APCI-1500 and create the device node 
# under /dev/apci1500 and the minor number of the board.

DRIVER_NAME="apci1500"
BOARD_NAME="apci1500"
MODULE_NAME="$BOARD_NAME.ko"
VENDOR_DEVICE_ID="10e880fc"

# Special version of the APCI-1500
# VENDOR_DEVICE_ID="15b8100d"

# checking privileges
if [ `id -u` -ne 0 ];
then
	echo "$0: You must have root privileges to run this script shell"
	exit 1
fi

# Test the kernel version
if [ `uname -r | cut -d'.' -f 2` -ne 6 ];
then
	echo "$0: This script is only for kernel 2.6.X"
	exit 1
fi

# Surch the number of apci-xxxx in the computer
NBOARDS=$(rgrep -c $VENDOR_DEVICE_ID /proc/bus/pci/devices)

# Board found?
if [ $? -eq 1 ]; then
	echo "Fail to detectd $BOARD_NAME"
	exit 1
fi

if [ $NBOARDS -eq 0 ]; then
	echo "No $BOARD_NAME detected"
	exit 1
fi

echo "$NBOARDS $BOARD_NAME detected"

cat /proc/modules | rgrep $BOARD_NAME > /dev/null

if [ $? -eq 0 ]; then
	rmmod $MODULE_NAME > /dev/null
fi

insmod $MODULE_NAME

# Surch the major number
MAJOR=$(grep $DRIVER_NAME /proc/devices | cut -f 1 -d\ )

mkdir -p "/dev/$BOARD_NAME"
cd "/dev/$BOARD_NAME"

# Create nodes
i=0
while [ $i -lt $NBOARDS ]; do

	if [ -a "/dev/$BOARD_NAME/$i" ]; then
		rm "/dev/$BOARD_NAME/$i"
	fi

	mknod $i c $MAJOR $i
	chmod 666 /dev/$BOARD_NAME/$i	
	echo "Make node /dev/$BOARD_NAME/$i"

	i=$((i+1))
done

exit 0





