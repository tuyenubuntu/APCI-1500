from APCI_1500 import OSClass
import time

card = OSClass()
# card.set_output_memory(True)
# card.set_do(0)         # Bật output 1
# card.reset_do(0)  
# while True:
#     card.set_do(0)  
#     # time.sleep(0.5)
#     card.set_do(2) 
#     time.sleep(0.5)
#     card.reset_do(0)  
#     # time.sleep(0.5)
#     card.reset_do(2)
#     # card.get_do(0)
#     time.sleep(0.5)
#     # card.get_do(0)
    # time.sleep(0.5)
    # card.get_di(0)
    # time.sleep(1)
# card.reset_do(4)
# print("Input 1:", card.get_di(1))
# card.get_do(1)
# card.reset_do(1)       # Tắt output 1
# card.reset_all_do()    # Tắt tất cả
# card.close()
# card.get_all_di()
# card.set_do(0)
card.reset_do(0)



while True:
    # card.set_do(0)
    # card.set_do(2)
    # card.reset_do(1)
    # card.reset_do(3)
    # card.get_do_status()
    # time.sleep(0.5)
    # card.reset_do(0)
    # card.reset_do(2)
    # card.set_do(1)
    # card.set_do(3)
    # print (card.get_do(15))
    print (card.get_do(0))
    time.sleep(0.5)
