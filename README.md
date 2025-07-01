# APCI-1500

# APCI1500 Python

These are optimized functions, simple for IO communication on APCI1500 IO Card.

## Contents

- [Overview](#overview)
- [Installation](#installation)
- [Usage](#usage)
  - [Initialize and Open Board](#initialize-and-open-board)
  - [Read Digital Inputs](#read-digital-inputs)
  - [Get Digital Outputs](#get-digital-ouputs)
  - [Control Digital Outputs](#control-digital-outputs)
  - [Set Digital Output Memory](#set-digital-output-memory)
  - [Close Board](#close-board)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

## Overview

This library simplifies interaction with the PCI1500 board by wrapping its C-based DLL functions into Python methods. The library supports:

- Read digital input channels.
- Get digital input channels.
- Control 16 digital output channels.
- management digital output memory state.
## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/tuyenubuntu/apci-1500.git
   cd APCI-1500
   git switch linux
   ```
2. Navigate to the library folder:
   ```bash
   cd lib_linux
   ```
3. Ensure the `PCI1500.so` file is in the `lib_linux` folder.

## Usage

### Initialize and Open Board

```python
from apci1500 import OSClass

# Initialize the library
pci = OSClass()
```

### Read Digital Inputs
#### Read 1 Digital Inputs
```python
# Read the 16 digital inputs
in_channel = 1
in_channel_val = pci.get_di(in_channel)
print(f"Status input channel {in_channel}: {in_channel_val}")
```

### Get Digital Ouputs
#### Get 1 Digital Outputs
```python
out_channel = 2
out_channel_val = get_do(out_channel)
print(f"Status output channel {out_channel}: {out_channel_val}")
```


### Control Digital Outputs
#### Turn On/Off Specific Channels

```python
# Turn on channel 0
pci.set_do(0)

# Turn off channel 0
pci.reset_do(0)
```

#### Turn Off All Channels

```python
# Turn off all outputs
pci.reset_all_do()
```

### Close Board

```python
# Close the board
pci.close_board()
```

## Troubleshooting

- Ensure the `PCI1500.so` file is located in the correct path as specified during initialization.
- Verify the board index if you have multiple boards connected.
- If functions return errors, refer to the PCI1500 documentation for error codes.
- If the `PCI1500.so` file is missing or the system lacks drivers for the IO PCI-1500 card, visit the manufacturer's website to download the correct driver (ensure the driver matches your operating system version and PCI slot type on your motherboard): [ADDI-DATA Drivers](https://www.addi-data.com/drivers). And recompile the library in the 'sample' folder: 

```bash
cd drivers/addidata/apci1500/samples
make clean & make
```

![Driver Download Instructions](/Documentation/pic_wrapper/driver_linux.png) 

## Contributing

Feel free to open issues or submit pull requests to improve this library. Contributions are welcome!

## License

This library provides a Python wrapper for the PCI1500 DLL, which is part of the software suite provided by ADDI-DATA. The original DLL and associated tools can be obtained from ADDI-DATA's official website: [https://www.addi-data.com/drivers](https://www.addi-data.com/drivers).

The wrapper code in this repository is distributed under the MIT License. See the `LICENSE` file for details.



