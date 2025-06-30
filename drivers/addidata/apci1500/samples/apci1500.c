/* apci1500.c - Shared library wrapper for APCI-1500 Linux driver */

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "apci1500.h"

#define DEVICE_PATH "/dev/apci1500/0"

static int apci1500_fd = -1;

int apci1500_open()
{
    apci1500_fd = open(DEVICE_PATH, O_RDWR);
    if (apci1500_fd < 0)
    {
        perror("Failed to open APCI1500 device");
        return -1;
    }
    return 0;
}

int apci1500_close()
{
    if (apci1500_fd >= 0)
    {
        close(apci1500_fd);
        apci1500_fd = -1;
    }
    return 0;
}

int apci1500_set_output_memory(int enable)
{
    uint8_t dummy = 0;
    int cmd = enable ? CMD_APCI1500_SetOutputMemoryOn : CMD_APCI1500_SetOutputMemoryOff;
    if (apci1500_fd < 0)
        return -ENODEV;
    return ioctl(apci1500_fd, cmd, &dummy);
}

int apci1500_set_output_on(int channel)
{
    if (apci1500_fd < 0)
        return -ENODEV;
    int hw_channel = channel + 1;
    return ioctl(apci1500_fd, CMD_APCI1500_Set1DigitalOutputOn, (unsigned long)hw_channel);
}

int apci1500_set_output_off(int channel)
{
    if (apci1500_fd < 0)
        return -ENODEV;
    int hw_channel = channel + 1;
    return ioctl(apci1500_fd, CMD_APCI1500_Set1DigitalOutputOff, (unsigned long)hw_channel);
}

int apci1500_reset_all_outputs()
{
    if (apci1500_fd < 0)
        return -ENODEV;
    return ioctl(apci1500_fd, CMD_APCI1500_Set16DigitalOutputOff, 0xFFFF);
}

int apci1500_read_input(int channel, int *value)
{
    if (apci1500_fd < 0)
        return -ENODEV;
    uint8_t ch = (uint8_t)(channel + 1);
    uint8_t val = ch;
    int ret = ioctl(apci1500_fd, CMD_APCI1500_Read1DigitalInput, &val);
    if (ret == 0)
        *value = val;
    return ret;
}

int apci1500_get_all_inputs(uint32_t *value)
{
    if (apci1500_fd < 0)
        return -ENODEV;
    return ioctl(apci1500_fd, CMD_APCI1500_Read16DigitalInput, value);
}


int apci1500_get_output_status(uint32_t *status) {
    if (apci1500_fd < 0) {
        fprintf(stderr, "Device not available: apci1500_fd is invalid (fd=%d)\n", apci1500_fd);
        return -ENODEV;
    }

    int ret = ioctl(apci1500_fd, CMD_APCI1500_Get16DigitalOutput, status);
    if (ret == -1) {
        fprintf(stderr, "ioctl failed: %s (errno=%d)\n", strerror(errno), errno);
        fflush(stderr);
    }

    return ret;
}