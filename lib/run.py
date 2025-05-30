from pci1500 import PCI1500
import time

# creat Ob PCI1500
# pci_device = PCI1500()

# # open board PCI1500
# board_handle = pci_device.open_board()

# Đọc input
# count = 0
# while board_handle:
#     print (count)
#     for i in range(16):
#         inputs = pci_device.read_16_inputs_status(board_handle)

#         print(f"Inputs: {inputs}")
#     time.sleep(3)
#     count = count + 1 


# Tắt output
# pci_device.set_digital_output_memory(board_handle, enable=True)
# while board_handle:
#     pci_device.set_output_on(board_handle, 15)
#     time.sleep(0.5)
#     pci_device.set_output_off(board_handle, 15)
#     time.sleep(0.5)

# #pci_device.set_digital_output_memory(board_handle, enable=True)

# # Đóng board PCI1500
# pci_device.close_board(board_handle)
# pci_device.set_output_off(board_handle, 15)
pci = PCI1500()
handle = pci.open_board()
# if handle:
#     pci_device.close_board(handle)
#     print ("Done")


# pci = PCI1500()
# handle = pci.open_board()

# if handle:
#     if pci.reset_board_interrupt_routine(handle):
#         print("Interrupt routine reset successfully.")
#     else:
#         print("Failed to reset interrupt routine.")


# if handle:
#     status = pci.get_outputs_status(handle, 8)
#     print(f"Output Status: {status}")
#     pci.close_board(handle)



# if handle:
#     status = pci.read_inputs_status(handle, 1)
#     print(f"Input Status: {status}")
#     pci.close_board(handle)

if handle:
    # pci_device.set_digital_output_memory(handle, enable=True)
    # pci.set_output_on(handle,1)
    pci.set_output_off(handle,1)
    # pci.set_all_outputs_off(handle)

# if handle:
    status = pci.get_16_outputs_status(handle)
    
    print(f"Output Status: {status}")
    pci.close_board(handle)