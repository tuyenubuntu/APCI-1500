from apci1500 import APCI1500
import time

pci = APCI1500()
handle = pci.open_board()


if handle:

    channel = 16
    
    # pci.set_output_off(handle, channel)
    pci.set_digital_output_memory(handle, enable=True)
    pci.set_all_outputs_off(handle)
    input_val = pci.get_16_outputs_status(handle)
    channels = channel
    time.sleep(2)
    print(f" status: {input_val}")