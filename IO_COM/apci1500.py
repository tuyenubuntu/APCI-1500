import ctypes

class APCI1500:
    def __init__(self, dll_path="apci1500/PCI1500.dll"):
        # Load the DLL
        self.pci1500 = ctypes.WinDLL(dll_path)
        
        # Define all required functions and their argument types
        self.i_PCI1500_OpenBoardViaIndex = self.pci1500.i_PCI1500_OpenBoardViaIndex
        self.i_PCI1500_OpenBoardViaIndex.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_void_p)]
        self.i_PCI1500_OpenBoardViaIndex.restype = ctypes.c_int

        self.i_PCI1500_CloseBoard = self.pci1500.i_PCI1500_CloseBoard
        self.i_PCI1500_CloseBoard.argtypes = [ctypes.c_void_p]
        self.i_PCI1500_CloseBoard.restype = ctypes.c_int

        self.i_PCI1500_Read1DigitalInput = self.pci1500.i_PCI1500_Read1DigitalInput
        self.i_PCI1500_Read1DigitalInput.argtypes = [ctypes.c_void_p, ctypes.c_ubyte, ctypes.POINTER(ctypes.c_ubyte)]
        self.i_PCI1500_Read1DigitalInput.restype = ctypes.c_int

        self.i_PCI1500_Set1DigitalOutputOn = self.pci1500.i_PCI1500_Set1DigitalOutputOn
        self.i_PCI1500_Set1DigitalOutputOn.argtypes = [ctypes.c_void_p, ctypes.c_byte]
        self.i_PCI1500_Set1DigitalOutputOn.restype = ctypes.c_int

        self.i_PCI1500_Set1DigitalOutputOff = self.pci1500.i_PCI1500_Set1DigitalOutputOff
        self.i_PCI1500_Set1DigitalOutputOff.argtypes = [ctypes.c_void_p, ctypes.c_byte]
        self.i_PCI1500_Set1DigitalOutputOff.restype = ctypes.c_int

        self.i_PCI1500_Set16DigitalOutputsOff = self.pci1500.i_PCI1500_Set16DigitalOutputsOff
        self.i_PCI1500_Set16DigitalOutputsOff.argtypes = [ctypes.c_void_p, ctypes.c_ushort]
        self.i_PCI1500_Set16DigitalOutputsOff.restype = ctypes.c_int

        self.i_PCI1500_Get16DigitalOutputsStatus = self.pci1500.i_PCI1500_Get16DigitalOutputsStatus
        self.i_PCI1500_Get16DigitalOutputsStatus.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ushort)]
        self.i_PCI1500_Get16DigitalOutputsStatus.restype = ctypes.c_int

        self.i_PCI1500_SetDigitalOutputMemoryOff = self.pci1500.i_PCI1500_SetDigitalOutputMemoryOff
        self.i_PCI1500_SetDigitalOutputMemoryOff.argtypes = [ctypes.c_void_p]
        self.i_PCI1500_SetDigitalOutputMemoryOff.restype = ctypes.c_int

        self.i_PCI1500_SetDigitalOutputMemoryOn = self.pci1500.i_PCI1500_SetDigitalOutputMemoryOn
        self.i_PCI1500_SetDigitalOutputMemoryOn.argtypes = [ctypes.c_void_p]
        self.i_PCI1500_SetDigitalOutputMemoryOn.restype = ctypes.c_int

        # Open board
        self.board_handle = self.open_board(board_index=0)

    def open_board(self, board_index=0):
        """
        Open PCI1500 board via index.
        :param board_index: Index of the board, default is 0.
        :return: Board handle.
        """
        board_handle = ctypes.c_void_p()
        result = self.i_PCI1500_OpenBoardViaIndex(board_index, ctypes.byref(board_handle))
        if result != 0:
            print(f"Error opening board: {result}")
            return None
        return board_handle

    def close_board(self):
        """
        Close PCI1500 board.
        :param board_handle: Handle of the board.
        :return: Error code if any, 0 if successful.
        """
        result = self.i_PCI1500_CloseBoard(self.board_handle)
        print(f"Close board {self.board_handle} successful")
        return result
    
    def read_di(self, channel):
        """
        Read value from a specific digital input channel.
        :param board_handle: Handle of the board.
        :param channel: Channel number (1-16).
        :return: 0 or 1 for input status, or None on error.
        """
        channels = channel - 1
        if channel < 1 or channel > 16:
            raise ValueError("Channel must be between 1 and 16")
        value = ctypes.c_ubyte()
        result = self.i_PCI1500_Read1DigitalInput(self.board_handle, ctypes.c_ubyte(channels), ctypes.byref(value))
        if result != 0:
            print(f"Error reading input channel {channel}: {result}")
            return None
        return value.value
    
    def get_do(self, channel):
        """
        Get current 16 (1 --> 16) digital output status with bit order reversed.
        :param board_handle: Handle of the board.
        :return: 16-bit binary string representing reversed output status or None on error.
        """
        output_status = ctypes.c_ushort(0)
        result = self.i_PCI1500_Get16DigitalOutputsStatus(self.board_handle, ctypes.byref(output_status))
        if result != 0:
            print(f"Error getting digital outputs status: {result}")
            return None

        # Convert to 16-bit binary and reverse the bit string
        bit_string = bin(output_status.value)[2:].zfill(16)
        reversed_bit_string = bit_string[::-1]
        output_status = reversed_bit_string[channel - 1]
        return output_status

    def reset_do(self, channel):
        """
        Turn off output at a specific channel.
        :param board_handle: Handle of the board.
        :param channel: Channel (1-16) to turn off the output.
        :return: Error code if any, 0 if successful.
        """
        self.set_digital_output_memory(enable=True)
        channels = channel -1
        if channel < 1 or channel > 16:
            raise ValueError("Channel must be between 1 and 16")
        result = self.i_PCI1500_Set1DigitalOutputOff(self.board_handle, ctypes.c_byte(channels))
        if result != 0:
            print(f"Error turning off output: {result}")
        else:
            print(f"Output {channel} turned off.")
        return result

    def set_do(self, channel):
        """
        Turn on output at a specific channel.
        :param board_handle: Handle of the board.
        :param channel: Channel (1-16) to turn on the output.
        :return: Error code if any, 0 if successful.
        """
        self.set_digital_output_memory(enable=True)
        channels = channel -1
        if channel < 1 or channel > 16:
            raise ValueError("Channel must be between 1 and 16")
        result = self.i_PCI1500_Set1DigitalOutputOn(self.board_handle, ctypes.c_byte(channels))
        if result != 0:
            print(f"Error turning on output: {result}")
        else:
            print(f"Output {channel} turned on.")
        return result

    def reset_all_do(self):
        """
        Turn off all outputs (channels 1 to 16).
        :param board_handle: Handle of the board.
        :return: Error code if any, 0 if successful.
        """
        result = self.i_PCI1500_Set16DigitalOutputsOff(self.board_handle, 0xFFFF)
        if result != 0:
            print(f"Error turning off all outputs: {result}")
        else:
            print("All outputs turned off.")
        return result

    def set_digital_output_memory(self, enable=True):
        """
        *When you enable/disable a digital output channel, 
        the other channels retain their current state.
        *Enable or disable the digital output memory.
        :param board_handle: Handle of the board.
        :param enable: True to enable, False to disable.
        :return: Error code if any, 0 if successful.
        """
        if enable:
            result = self.i_PCI1500_SetDigitalOutputMemoryOn(self.board_handle)
            if result != 0:
                print(f"Error enabling digital output memory: {result}")
            else:
                print("Digital output memory enabled.")
        else:
            result = self.i_PCI1500_SetDigitalOutputMemoryOff(self.board_handle)
            if result != 0:
                print(f"Error disabling digital output memory: {result}")
            else:
                print("Digital output memory disabled.")
        return result
