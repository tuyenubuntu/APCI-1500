import ctypes
import platform


#########------Windows--------#########
class APCI_1500_Windows:
    def __init__(self, dll_path="PCI1500.dll"):
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

    def get_di(self, id):
        """
        Read value from a specific digital input id.
        :param board_handle: Handle of the board.
        :param id: id number (0-15).
        :return: 0 or 1 for input status, or None on error.
        """

        if id < 0 or id > 15:
            raise ValueError("id must be between 0 and 15")
        value = ctypes.c_ubyte()
        result = self.i_PCI1500_Read1DigitalInput(self.board_handle, ctypes.c_ubyte(id), ctypes.byref(value))
        if result != 0:
            print(f"Error reading input id {id}: {result}")
            return None
        return value.value
    
    def set_do(self, id):
        """
        Turn on output at a specific id.
        :param board_handle: Handle of the board.
        :param id: id (0-15) to turn on the output.
        :return: Error code if any, 0 if successful.
        """
        self.set_digital_output_memory(enable=True)
        if id < 0 or id > 15:
            raise ValueError("id must be between 0 and 15")
        result = self.i_PCI1500_Set1DigitalOutputOn(self.board_handle, ctypes.c_byte(id))
        if result != 0:
            print(f"Error turning on output: {result}")
        else:
            print(f"Output {id} turned on.")
        return result
    
    def reset_do(self, id):
        """
        Turn off output at a specific id.
        :param board_handle: Handle of the board.
        :param id: id (0-15) to turn off the output.
        :return: Error code if any, 0 if successful.
        """
        self.set_digital_output_memory(enable=True)

        if id < 0 or id > 15:
            raise ValueError("id must be between 0 and 15")
        result = self.i_PCI1500_Set1DigitalOutputOff(self.board_handle, ctypes.c_byte(id))
        # if result != 0:
        #     print(f"Error turning off output {id}: {result}")
        # else:
        #     print(f"Output {id} turned off.")
        return result

    def get_do(self, id):
        """
        Get current 16 (0 --> 15) digital output status with bit order reversed.
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
        output_status = reversed_bit_string[id]
        return output_status
        
    def reset_all_do(self):
        """
        Turn off all outputs (channels 1 to 16).
        :param board_handle: Handle of the board.
        :return: Error code if any, 0 if successful.
        """
        self.set_digital_output_memory(enable=True)
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
            # if result != 0:
            #     print(f"Error enabling digital output memory: {result}")
            # else:
            #     print("Digital output memory enabled.")
        else:
            result = self.i_PCI1500_SetDigitalOutputMemoryOff(self.board_handle)
            # if result != 0:
            #     print(f"Error disabling digital output memory: {result}")
            # else:
            #     print("Digital output memory disabled.")
        return result

#########------Linux--------#########
class APCI_1500_Linux:
    def __init__(self, so_path="./PCI1500.so"):
        #Load .so
        print(f"[INFO] Loading shared library: {so_path}")
        self.lib = ctypes.CDLL(so_path)
        # Define all required functions and their argument types
        self.lib.apci1500_open.restype = ctypes.c_int
        self.lib.apci1500_close.restype = ctypes.c_int
        self.lib.apci1500_set_output_memory.argtypes = [ctypes.c_int]
        self.lib.apci1500_set_output_memory.restype = ctypes.c_int
        self.lib.apci1500_set_output_on.argtypes = [ctypes.c_int]
        self.lib.apci1500_set_output_on.restype = ctypes.c_int
        self.lib.apci1500_set_output_off.argtypes = [ctypes.c_int]
        self.lib.apci1500_set_output_off.restype = ctypes.c_int
        self.lib.apci1500_reset_all_outputs.restype = ctypes.c_int
        self.lib.apci1500_read_input.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
        self.lib.apci1500_read_input.restype = ctypes.c_int
        self.lib.apci1500_get_all_inputs.argtypes = [ctypes.POINTER(ctypes.c_uint32)]
        self.lib.apci1500_get_all_inputs.restype = ctypes.c_int
        # self.lib.apci1500_get_output_status.argtypes = [ctypes.POINTER(ctypes.c_uint32)]
        # self.lib.apci1500_get_output_status.restype = ctypes.c_int

        self.lib.apci1500_get_output_status.argtypes = [ctypes.POINTER(ctypes.c_uint16)]
        self.lib.apci1500_get_output_status.restype = ctypes.c_int


        
        # Open device
        result = self.lib.apci1500_open()
        if result != 0:
            raise RuntimeError("❌ Failed to open APCI1500 device")
        print("[✅] Device opened successfully.")

        self.board_handle = True 

    def open_board(self, board_index=0):
        print(f"[INFO] Opening board index {board_index} (dummy in Linux)...")
        return self.board_handle

    def close_board(self):
        result = self.lib.apci1500_close()
        if result == 0:
            print("[✅] Device closed successfully.")
        else:
            print("[❌] Failed to close device.")
        return result

    def get_di(self, id):
        if not (0 <= id <= 15):
            raise ValueError("Input ID must be in 0–15")
        val = ctypes.c_int()
        result = self.lib.apci1500_read_input(id, ctypes.byref(val))
        if result != 0:
            print(f"❌ Error reading input {id}")
            return None
        print(f"[INFO] Input {id} value: {val.value}")
        return val.value

    def set_do(self, id):
        self.set_digital_output_memory(True)
        if not (0 <= id <= 15):
            raise ValueError("Output ID must be in 0–15")
        result = self.lib.apci1500_set_output_on(id)
        if result == 0:
            print(f"[✅] Output {id} turned ON.")
        else:
            print(f"[❌] Failed to turn ON output {id}")
        return result

    def reset_do(self, id):
        self.set_digital_output_memory(True)
        if not (0 <= id <= 15):
            raise ValueError("Output ID must be in 0–15")
        result = self.lib.apci1500_set_output_off(id)
        if result == 0:
            print(f"[✅] Output {id} turned OFF.")
        else:
            print(f"[❌] Failed to turn OFF output {id}")
        return result

    def reset_all_do(self):
        self.set_digital_output_memory(True)
        result = self.lib.apci1500_reset_all_outputs()
        if result == 0:
            print("[✅] All outputs turned OFF.")
        else:
            print("[❌] Failed to reset all outputs.")
        return result

    def set_digital_output_memory(self, enable=True):
        print(f"[INFO] Setting output memory: {'ON' if enable else 'OFF'}")
        return self.lib.apci1500_set_output_memory(1 if enable else 0)

    def get_all_di(self):
        val = ctypes.c_uint32()
        result = self.lib.apci1500_get_all_inputs(ctypes.byref(val))
        if result != 0:
            print("❌ Error reading all inputs")
            return None
        print(f"[INFO] All input bits: {val.value:016b}")
        return val.value
    
    # def get_do(self, id):
    #     if not (0 <= id <= 15):
    #         raise ValueError("ID must be 0–15")
    #     val = ctypes.c_uint32()
    #     result = self.lib.apci1500_get_output_status(ctypes.byref(val))
    #     print(result)
    #     if result != 0:
    #         raise RuntimeError("❌ Failed to get output status")
    #     bit_string = bin(val.value)[2:].zfill(16)[::-1]
    #     print(f"[INFO] Output status: {bit_string}")
    #     return bit_string[id]


    # def get_do_status(self):
    #     val = ctypes.c_uint16()
    #     result = self.lib.apci1500_get_output_status(ctypes.byref(val))
    #     if result != 0:
    #         raise RuntimeError("❌ Error getting DO status")
    #     print(f"[INFO] Output status: {val.value:08b}")
    #     return val.value
    
    def get_do(self, id):
        """
        Get current 16 (0 --> 15) digital output status with bit order reversed.
        :param board_handle: Handle of the board.
        :return: 16-bit binary string representing reversed output status or None on error.
        """
        output_status = ctypes.c_ushort(0)
        result = self.lib.apci1500_get_output_status(ctypes.byref(output_status))
        if result != 0:
            print(f"Error getting digital outputs status: {result}")
            return None

        # Convert to 16-bit binary and reverse the bit string
        bit_string = bin(output_status.value)[2:].zfill(16)
        reversed_bit_string = bit_string[::-1]
        output_status = reversed_bit_string[id]
        return output_status


    
if platform.system() == "Windows":
    OSClass = APCI_1500_Windows
else:
    OSClass = APCI_1500_Linux