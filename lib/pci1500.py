import ctypes

class PCI1500:
    def __init__(self, dll_path="pci1500/PCI1500.dll"):
        # Load the DLL
        self.pci1500 = ctypes.WinDLL(dll_path)
        
        # Define functions and their argument types
        self._define_functions()

    def _define_functions(self):
        # Define all required functions and their argument types
        self.i_PCI1500_OpenBoardViaIndex = self.pci1500.i_PCI1500_OpenBoardViaIndex
        self.i_PCI1500_OpenBoardViaIndex.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_void_p)]
        self.i_PCI1500_OpenBoardViaIndex.restype = ctypes.c_int

        self.i_PCI1500_ResetBoardIntRoutine = self.pci1500.i_PCI1500_ResetBoardIntRoutine
        self.i_PCI1500_ResetBoardIntRoutine.argtypes = [ctypes.c_void_p]  # Board handle
        self.i_PCI1500_ResetBoardIntRoutine.restype = ctypes.c_int        # Return type (usually 0 = success)


        self.i_PCI1500_Set1DigitalOutputOn = self.pci1500.i_PCI1500_Set1DigitalOutputOn
        self.i_PCI1500_Set1DigitalOutputOn.argtypes = [ctypes.c_void_p, ctypes.c_byte]
        self.i_PCI1500_Set1DigitalOutputOn.restype = ctypes.c_int

        self.i_PCI1500_Set1DigitalOutputOff = self.pci1500.i_PCI1500_Set1DigitalOutputOff
        self.i_PCI1500_Set1DigitalOutputOff.argtypes = [ctypes.c_void_p, ctypes.c_byte]
        self.i_PCI1500_Set1DigitalOutputOff.restype = ctypes.c_int

        self.i_PCI1500_CloseBoard = self.pci1500.i_PCI1500_CloseBoard
        self.i_PCI1500_CloseBoard.argtypes = [ctypes.c_void_p]
        self.i_PCI1500_CloseBoard.restype = ctypes.c_int

        self.i_PCI1500_Read16DigitalInputs = self.pci1500.i_PCI1500_Read16DigitalInputs
        self.i_PCI1500_Read16DigitalInputs.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ushort)]
        self.i_PCI1500_Read16DigitalInputs.restype = ctypes.c_int

        self.i_PCI1500_Set16DigitalOutputsOff = self.pci1500.i_PCI1500_Set16DigitalOutputsOff
        self.i_PCI1500_Set16DigitalOutputsOff.argtypes = [ctypes.c_void_p]
        self.i_PCI1500_Set16DigitalOutputsOff.restype = ctypes.c_int

        self.i_PCI1500_Set16DigitalOutputsOn = self.pci1500.i_PCI1500_Set16DigitalOutputsOn
        self.i_PCI1500_Set16DigitalOutputsOn.argtypes = [ctypes.c_void_p]
        self.i_PCI1500_Set16DigitalOutputsOn.restype = ctypes.c_int

        self.i_PCI1500_SetDigitalOutputMemoryOff = self.pci1500.i_PCI1500_SetDigitalOutputMemoryOff
        self.i_PCI1500_SetDigitalOutputMemoryOff.argtypes = [ctypes.c_void_p]
        self.i_PCI1500_SetDigitalOutputMemoryOff.restype = ctypes.c_int

        self.i_PCI1500_SetDigitalOutputMemoryOn = self.pci1500.i_PCI1500_SetDigitalOutputMemoryOn
        self.i_PCI1500_SetDigitalOutputMemoryOn.argtypes = [ctypes.c_void_p]
        self.i_PCI1500_SetDigitalOutputMemoryOn.restype = ctypes.c_int

        self.i_PCI1500_Get16DigitalOutputsStatus = self.pci1500.i_PCI1500_Get16DigitalOutputsStatus
        self.i_PCI1500_Get16DigitalOutputsStatus.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ushort)]
        self.i_PCI1500_Get16DigitalOutputsStatus.restype = ctypes.c_int


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

    def close_board(self, board_handle):
        """
        Close PCI1500 board.
        :param board_handle: Handle of the board.
        :return: Error code if any, 0 if successful.
        """
        result = self.i_PCI1500_CloseBoard(board_handle)
        return result
    
    def reset_board_interrupt_routine(self, board_handle):
        """
        Reset the interrupt routine of the board.
        :param board_handle: Handle of the board.
        :return: True if success, False otherwise.
        """
        result = self.i_PCI1500_ResetBoardIntRoutine(board_handle)
        if result != 0:
            print(f"Error resetting board interrupt routine: {result}")
            return False
        return True


    def read_16_inputs_status(self, board_handle):
        """
        Read values from the 16 input channels of the PCI1500 board.
        :param board_handle: Handle of the board.
        :return: Value read from input channels.
        """
        channels_value = ctypes.c_ushort(0)
        result = self.i_PCI1500_Read16DigitalInputs(board_handle, ctypes.byref(channels_value))

        if result != 0:
            print(f"Error reading inputs: {result}")
            return None
        bit_string = bin(channels_value.value)[2:].zfill(16)
        reversed_bit_string = bit_string[::-1]
        return reversed_bit_string
    
    def read_inputs_status(self, board_handle, channel):
        input_status = self.read_16_inputs_status(board_handle)[channel - 1]
        return input_status

    
    def get_16_outputs_status(self, board_handle):
        """
        Get current 16 digital output status with bit order reversed.
        :param board_handle: Handle of the board.
        :return: 16-bit binary string representing reversed output status or None on error.
        """
        output_status = ctypes.c_ushort(0)
        result = self.i_PCI1500_Get16DigitalOutputsStatus(board_handle, ctypes.byref(output_status))

        if result != 0:
            print(f"Error getting digital outputs status: {result}")
            return None

        # Convert to 16-bit binary and reverse the bit string
        bit_string = bin(output_status.value)[2:].zfill(16)
        reversed_bit_string = bit_string[::-1]

        return reversed_bit_string
    
    def get_outputs_status(self, board_handle, channel):
        output_status = self.get_16_outputs_status(board_handle)[channel - 1]
        return output_status
        



    def set_output_off(self, board_handle, channel):
        """
        Turn off output at a specific channel.
        :param board_handle: Handle of the board.
        :param channel: Channel (1-16) to turn off the output.
        :return: Error code if any, 0 if successful.
        """
        channels = channel -1
        if channel < 1 or channel > 16:
            raise ValueError("Channel must be between 0 and 15")

        result = self.i_PCI1500_Set1DigitalOutputOff(board_handle, ctypes.c_byte(channels))

        if result != 0:
            print(f"Error turning off output: {result}")
        else:
            print(f"Output {channel} turned off.")

        return result

    def set_output_on(self, board_handle, channel):
        """
        Turn on output at a specific channel.
        :param board_handle: Handle of the board.
        :param channel: Channel (1-16) to turn on the output.
        :return: Error code if any, 0 if successful.
        """
        channels = channel -1
        if channel < 1 or channel > 16:
            raise ValueError("Channel must be between 0 and 15")

        result = self.i_PCI1500_Set1DigitalOutputOn(board_handle, ctypes.c_byte(channels))

        if result != 0:
            print(f"Error turning on output: {result}")
        else:
            print(f"Output {channel} turned on.")

        return result

    def set_all_outputs_off(self, board_handle):
        """
        Turn off all outputs (channels 0 to 15).
        :param board_handle: Handle of the board.
        :return: Error code if any, 0 if successful.
        """
        result = self.i_PCI1500_Set16DigitalOutputsOff(board_handle)

        if result != 0:
            print(f"Error turning off all outputs: {result}")
        else:
            print("All outputs turned off.")

        return result

    def set_all_outputs_on(self, board_handle):
        """
        Turn on all outputs (channels 0 to 15).
        :param board_handle: Handle of the board.
        :return: Error code if any, 0 if successful.
        """
        result = self.i_PCI1500_Set16DigitalOutputsOn(board_handle)

        if result != 0:
            print(f"Error turning on all outputs: {result}")
        else:
            print("All outputs turned on.")

        return result

    def set_digital_output_memory(self, board_handle, enable=True):
        """
        Enable or disable the digital output memory.
        :param board_handle: Handle of the board.
        :param enable: True to enable, False to disable.
        :return: Error code if any, 0 if successful.
        """
        if enable:
            result = self.i_PCI1500_SetDigitalOutputMemoryOn(board_handle)
            if result != 0:
                print(f"Error enabling digital output memory: {result}")
            else:
                print("Digital output memory enabled.")
        else:
            result = self.i_PCI1500_SetDigitalOutputMemoryOff(board_handle)
            if result != 0:
                print(f"Error disabling digital output memory: {result}")
            else:
                print("Digital output memory disabled.")

        return result
