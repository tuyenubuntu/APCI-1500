from APCI_1500 import OSClass
import time

pci = OSClass()

#Your logic
#Ex:
pci.set_do(0)
pci.set_do(2)
while True:
    print (pci.get_do(0))
    print (pci.get_do(2))
    time.sleep(0.5)
