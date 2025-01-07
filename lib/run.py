from pci1500 import PCI1500
import time

# creat Ob PCI1500
pci_device = PCI1500()

# open board PCI1500
board_handle = pci_device.open_board()

# Đọc input
# count = 0
# while board_handle:
#     print (count)
#     for i in range(16):
#         inputs = pci_device.read_inputs(board_handle)[i]

#         print(f"Inputs {i}: {inputs}")
#     time.sleep(3)
#     count = count + 1 


# Tắt output
return_value = pci_device.set_output_off(board_handle, 15)
print (return_value)

pci_device.set_digital_output_memory(board_handle, enable=True)

# Đóng board PCI1500
pci_device.close_board(board_handle)
