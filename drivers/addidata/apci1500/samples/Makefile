# # change that if you want to cross-compile 
# # CC=mipsel-linux-gcc

# ####################################################################
# # relative path of the addidata include directory
# # IF YOU ARE BUILDING THIS DRIVER OUTSIDE THE KERNEL SOURCE
# # PLEASE ADAPT THIS VARIABLE TO YOUR LOCAL INSTALLATION 
# ifeq ($(ADDIDATAINC),)
# ADDIDATAINC:=$(shell pwd)/../../../../include/linux/addidata
# endif
# ####################################################################

# OBJS:=sample_apci1500 sample_event sample_digital_outputs

# CFLAGS:=-Wall -D_ADDI_NO_WIN32_COMPAT

# all: $(OBJS)

# clean:
# 	-rm $(OBJS)

# # Compile the sample apps
# sample_apci1500: sample_apci1500.c
# 	$(CC) $(CFLAGS) -I$(ADDIDATAINC) $< -o $@

# # Compile the sample apps
# sample_event: sample_event.c
# 	$(CC) $(CFLAGS) -pthread -I$(ADDIDATAINC) $< -o $@

# sample_digital_outputs: sample_digital_outputs.c
# 	$(CC) $(CFLAGS) -I$(ADDIDATAINC) $< -o $@




# Compiler
CC = gcc

# Đường dẫn đến file include (nếu có)
ifeq ($(ADDIDATAINC),)
ADDIDATAINC := $(shell pwd)/../../../../include/linux/addidata
endif

# Compiler & Linker flags
CFLAGS := -Wall -fPIC -D_ADDI_NO_WIN32_COMPAT -I$(ADDIDATAINC)
LDFLAGS := -shared

# Source file nằm ở thư mục cha
SRC := apci1500.c
HDR := apci1500.h
LIBTARGET := PCI1500.so

all: $(LIBTARGET)

# Build shared library từ ../apci1500.c
$(LIBTARGET): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

clean:
	rm -f $(LIBTARGET)

