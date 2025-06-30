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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x8a05ec72, "i_APCI1500_StopTimerCounter1" },
	{ 0x7fa5fc1b, "i_APCI1500_EnableDisableTimerCounter1Interrupt" },
	{ 0x571c726d, "i_APCI1500_ResetBoardIntRoutine" },
	{ 0x67c6e554, "apci1500_get_lock" },
	{ 0x34db050b, "_raw_spin_lock_irqsave" },
	{ 0xd35cce70, "_raw_spin_unlock_irqrestore" },
	{ 0x5803e56b, "apci1500_lookup_board_by_index" },
	{ 0xd0ece50c, "i_APCI1500_SetBoardIntRoutine" },
	{ 0xa1e5b617, "i_APCI1500_InitTimerInputClock" },
	{ 0xa843c676, "i_APCI1500_InitTimerCounter1" },
	{ 0xfa5d84d8, "i_APCI1500_StartTimerCounter1" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x61c8abfe, "i_APCI1500_TestInterrupt" },
	{ 0x122c3a7e, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xb2b23fc2, "module_layout" },
};

MODULE_INFO(depends, "apci1500");


MODULE_INFO(srcversion, "9CF52D2CF24C343C2D36FA1");
