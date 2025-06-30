#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

KSYMTAB_FUNC(apci1500_lookup_board_by_index, "", "");
KSYMTAB_FUNC(APCI1500_SetIntCallback, "", "");
KSYMTAB_FUNC(APCI1500_ResetIntCallback, "", "");
KSYMTAB_FUNC(apci1500_get_lock, "", "");
KSYMTAB_FUNC(i_APCI1500_InitWatchdogCounter3, "", "");
KSYMTAB_FUNC(i_APCI1500_TriggerWatchdog, "", "");
KSYMTAB_FUNC(i_APCI1500_TriggerCounter3, "", "");
KSYMTAB_FUNC(i_APCI1500_StopCounter3, "", "");
KSYMTAB_FUNC(i_APCI1500_EnableDisableWatchdogCounter3Interrupt, "", "");
KSYMTAB_FUNC(i_APCI1500_StartCounter3, "", "");
KSYMTAB_FUNC(i_APCI1500_ReadCounter3, "", "");
KSYMTAB_FUNC(i_APCI1500_Read1DigitalInput, "", "");
KSYMTAB_FUNC(i_APCI1500_Read8DigitalInput, "", "");
KSYMTAB_FUNC(i_APCI1500_Read16DigitalInput, "", "");
KSYMTAB_FUNC(i_APCI1500_Set1DigitalOutputOn, "", "");
KSYMTAB_FUNC(i_APCI1500_Set1DigitalOutputOff, "", "");
KSYMTAB_FUNC(i_APCI1500_Set8DigitalOutputOn, "", "");
KSYMTAB_FUNC(i_APCI1500_Set8DigitalOutputOff, "", "");
KSYMTAB_FUNC(i_APCI1500_Set16DigitalOutputOn, "", "");
KSYMTAB_FUNC(i_APCI1500_Set16DigitalOutputOff, "", "");
KSYMTAB_FUNC(i_APCI1500_SetOutputMemoryOn, "", "");
KSYMTAB_FUNC(i_APCI1500_SetOutputMemoryOff, "", "");
KSYMTAB_FUNC(i_APCI1500_SetInputEventMask, "", "");
KSYMTAB_FUNC(i_APCI1500_StartInputEvent, "", "");
KSYMTAB_FUNC(i_APCI1500_StopInputEvent, "", "");
KSYMTAB_FUNC(i_APCI1500_InitTimerCounter1, "", "");
KSYMTAB_FUNC(i_APCI1500_ReadTimerCounter1, "", "");
KSYMTAB_FUNC(i_APCI1500_EnableDisableTimerCounter1Interrupt, "", "");
KSYMTAB_FUNC(i_APCI1500_StartTimerCounter1, "", "");
KSYMTAB_FUNC(i_APCI1500_TriggerTimerCounter1, "", "");
KSYMTAB_FUNC(i_APCI1500_StopTimerCounter1, "", "");
KSYMTAB_FUNC(i_APCI1500_InitTimerCounter2, "", "");
KSYMTAB_FUNC(i_APCI1500_ReadTimerCounter2, "", "");
KSYMTAB_FUNC(i_APCI1500_EnableDisableTimerCounter2Interrupt, "", "");
KSYMTAB_FUNC(i_APCI1500_StartTimerCounter2, "", "");
KSYMTAB_FUNC(i_APCI1500_TriggerTimerCounter2, "", "");
KSYMTAB_FUNC(i_APCI1500_StopTimerCounter2, "", "");
KSYMTAB_FUNC(i_APCI1500_SetBoardIntRoutine, "", "");
KSYMTAB_FUNC(i_APCI1500_ResetBoardIntRoutine, "", "");
KSYMTAB_FUNC(i_APCI1500_TestInterrupt, "", "");
KSYMTAB_FUNC(i_APCI1500_InitTimerInputClock, "", "");

SYMBOL_CRC(apci1500_lookup_board_by_index, 0x5803e56b, "");
SYMBOL_CRC(APCI1500_SetIntCallback, 0x9a7263d6, "");
SYMBOL_CRC(APCI1500_ResetIntCallback, 0xa6964872, "");
SYMBOL_CRC(apci1500_get_lock, 0x67c6e554, "");
SYMBOL_CRC(i_APCI1500_InitWatchdogCounter3, 0xb8335b85, "");
SYMBOL_CRC(i_APCI1500_TriggerWatchdog, 0x38faf13f, "");
SYMBOL_CRC(i_APCI1500_TriggerCounter3, 0x289880c9, "");
SYMBOL_CRC(i_APCI1500_StopCounter3, 0xe5ee027a, "");
SYMBOL_CRC(i_APCI1500_EnableDisableWatchdogCounter3Interrupt, 0x46509e75, "");
SYMBOL_CRC(i_APCI1500_StartCounter3, 0x0762c673, "");
SYMBOL_CRC(i_APCI1500_ReadCounter3, 0xfaf1a199, "");
SYMBOL_CRC(i_APCI1500_Read1DigitalInput, 0x10b35a34, "");
SYMBOL_CRC(i_APCI1500_Read8DigitalInput, 0xcc0048fa, "");
SYMBOL_CRC(i_APCI1500_Read16DigitalInput, 0x275db802, "");
SYMBOL_CRC(i_APCI1500_Set1DigitalOutputOn, 0xff6fe42c, "");
SYMBOL_CRC(i_APCI1500_Set1DigitalOutputOff, 0xb3bb19b8, "");
SYMBOL_CRC(i_APCI1500_Set8DigitalOutputOn, 0x62dba41d, "");
SYMBOL_CRC(i_APCI1500_Set8DigitalOutputOff, 0x161ec436, "");
SYMBOL_CRC(i_APCI1500_Set16DigitalOutputOn, 0x07bc2b87, "");
SYMBOL_CRC(i_APCI1500_Set16DigitalOutputOff, 0x0df17491, "");
SYMBOL_CRC(i_APCI1500_SetOutputMemoryOn, 0x5eb0ffff, "");
SYMBOL_CRC(i_APCI1500_SetOutputMemoryOff, 0xf41c28d8, "");
SYMBOL_CRC(i_APCI1500_SetInputEventMask, 0xd191623a, "");
SYMBOL_CRC(i_APCI1500_StartInputEvent, 0x025a36a6, "");
SYMBOL_CRC(i_APCI1500_StopInputEvent, 0x317b9d6d, "");
SYMBOL_CRC(i_APCI1500_InitTimerCounter1, 0xa843c676, "");
SYMBOL_CRC(i_APCI1500_ReadTimerCounter1, 0xb3f52748, "");
SYMBOL_CRC(i_APCI1500_EnableDisableTimerCounter1Interrupt, 0x7fa5fc1b, "");
SYMBOL_CRC(i_APCI1500_StartTimerCounter1, 0xfa5d84d8, "");
SYMBOL_CRC(i_APCI1500_TriggerTimerCounter1, 0xb41a5de7, "");
SYMBOL_CRC(i_APCI1500_StopTimerCounter1, 0x8a05ec72, "");
SYMBOL_CRC(i_APCI1500_InitTimerCounter2, 0xf6e0d2db, "");
SYMBOL_CRC(i_APCI1500_ReadTimerCounter2, 0xb2866f32, "");
SYMBOL_CRC(i_APCI1500_EnableDisableTimerCounter2Interrupt, 0xd2780605, "");
SYMBOL_CRC(i_APCI1500_StartTimerCounter2, 0x1d46a296, "");
SYMBOL_CRC(i_APCI1500_TriggerTimerCounter2, 0x53017ba9, "");
SYMBOL_CRC(i_APCI1500_StopTimerCounter2, 0x6d1eca3c, "");
SYMBOL_CRC(i_APCI1500_SetBoardIntRoutine, 0xd0ece50c, "");
SYMBOL_CRC(i_APCI1500_ResetBoardIntRoutine, 0x571c726d, "");
SYMBOL_CRC(i_APCI1500_TestInterrupt, 0x61c8abfe, "");
SYMBOL_CRC(i_APCI1500_InitTimerInputClock, 0xa1e5b617, "");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xc1514a3b, "free_irq" },
	{ 0x57c67651, "pci_enable_device" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x5a4896a8, "__put_user_2" },
	{ 0xbb36370a, "kill_fasync" },
	{ 0xfa5cdaeb, "class_destroy" },
	{ 0x9d5676bf, "__pci_register_driver" },
	{ 0xc0d281de, "pci_request_regions" },
	{ 0x37a0cba, "kfree" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0xe2964344, "__wake_up" },
	{ 0x34db050b, "_raw_spin_lock_irqsave" },
	{ 0xda5edba0, "pci_unregister_driver" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0x122c3a7e, "_printk" },
	{ 0x1000e51, "schedule" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xb2fd5ceb, "__put_user_4" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0xf641a686, "device_create" },
	{ 0x33c47e0e, "class_create" },
	{ 0x4c03a563, "random_kmalloc_seed" },
	{ 0xc3aaf0a9, "__put_user_1" },
	{ 0xb3feee07, "fasync_helper" },
	{ 0xd35cce70, "_raw_spin_unlock_irqrestore" },
	{ 0xb8e7ce2c, "__put_user_8" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x167e7f9d, "__get_user_1" },
	{ 0x1feaa674, "pci_release_regions" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x2f920aea, "__register_chrdev" },
	{ 0xc21bdf9, "device_destroy" },
	{ 0xab219350, "pci_disable_device" },
	{ 0xdc327b3c, "kmalloc_trace" },
	{ 0xe2c17b5d, "__SCT__might_resched" },
	{ 0x29ac0981, "kmalloc_caches" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xb2b23fc2, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("pci:v000010E8d000080FCsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000015B8d00001021sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "F48C7AB6A30B7834082EF25");
