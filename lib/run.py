from apci1500 import APCI1500
import time

pci = APCI1500()
handle = pci.open_board()


if handle:

    channel = 13
    input_val = pci.read_input_channel_status(handle, channel)
    channels = channel
    print(f"Channel {channels} status: {input_val}")