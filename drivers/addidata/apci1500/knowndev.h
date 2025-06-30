#ifndef __APCI1500_KNOWNDEV_H__
#define __APCI1500_KNOWNDEV_H__

void apci1500_known_dev_append(struct pci_dev * pdev);
void apci1500_known_dev_remove(struct pci_dev * pdev);

#endif // __APCI1500_KNOWNDEV_H__
