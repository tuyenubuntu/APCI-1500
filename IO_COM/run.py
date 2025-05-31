from apci1500 import APCI1500
import time


pci = APCI1500()
# handle = pci.open_board()


# if handle:
    # pci_device.set_digital_output_memory(handle, enable=True)
    # pci.set_output_on(handle,1)
    # pci.set_output_off(handle,1)
    # pci.set_all_outputs_off(handle)

# if handle:
    # channel = 16

    # read digital input
    # status = pci.read_di(handle,channel)
    # print(f"Input {channel} Status: {status}")

    # read digital output
    # status = pci.get_do(handle,channel)
    # print(f"output {channel} Status: {status}")
    # pci.close_board(handle)

    # set digital output
    # pci.set_do(handle, channel)

    # reset digital output
    # pci.reset_do(handle, channel)
out_channel = 4
in_channel = 1
# pci.set_do(out_channel)
# pci.reset_do(out_channel)
print ("result:", pci.reset_all_do())
out_channel_val = pci.get_do(out_channel)
print(f"Status output channel {out_channel}: {out_channel_val}")
# in_channel_val = pci.read_di(in_channel)
# print(f"Status input channel {in_channel}: {in_channel_val}")
# pci.close_board()