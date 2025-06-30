# the ADDIDATAINCLUDE variable may hold the path to the addidata-specific include directory
ifeq ($(ADDIDATAINC),)
# include directory has not been specified. suppose we are located inside the Linux kernel source tree
EXTRA_CFLAGS:=-I$(TOPDIR)/include/linux/addidata/ 
else
# use specified location
EXTRA_CFLAGS:=-I$(ADDIDATAINC) 
endif

EXTRA_CFLAGS+=-D_ADDI_NO_WIN32_COMPAT

# Objects that export symbols.
obj-$(CONFIG_APCI1500_IOCTL)	+= apci1500.o

# there is two version of the APCI 1500
# this one uses the newer version with built in watchdog
ifeq ($(CONFIG_APCI1500_UNIVERSAL_WATCHDOG),y)
	WATCHDOG_OBJ := watchdog-universal.o watchdog-universal-kapi.o
	EXTRA_CFLAGS+=-DCONFIG_APCI1500_UNIVERSAL_WATCHDOG=1
else
	# this one uses the watchdog embedded in Zilog chipset
	WATCHDOG_OBJ := watchdog-zilog.o watchdog-zilog-kapi.o
endif

# list of objects that make the module
apci1500-objs := knowndev.o main.o apci1500-api.o interrupt.o timercounter1.o timercounter2.o digIO.o events.o fs.o procfs.o $(WATCHDOG_OBJ) ioctl.o vtable.o digIO-kapi.o events-kapi.o timercounter1-kapi.o timercounter2-kapi.o interrupt-kapi.o interrupt-ioctl.o apci1500-kapi.o


# KERNEL 2.4 ------------------------------------------
ifeq ($(VERSION),2)
ifeq ($(PATCHLEVEL),4)

# The target object and module list name.
O_TARGET	:= driver.o

# Objects that export symbols.
export-objs	:= knowndev.o main.o digIO-kapi.o events-kapi.o timercounter1-kapi.o timercounter2-kapi.o interrupt-kapi.o apci1500-kapi.o watchdog-zilog-kapi.o

# The global Rules.make.
include $(TOPDIR)/Rules.make

# Link rules
apci1500.o: $(apci1500-objs)
	$(LD) -r -o $@ $(apci1500-objs)

endif
endif
