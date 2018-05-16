#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x6fb8d7bc, "module_layout" },
	{ 0x2dbb9eb8, "platform_device_unregister" },
	{ 0x215e56dd, "platform_driver_unregister" },
	{ 0x68403ddd, "platform_driver_register" },
	{ 0x3c6ddbbb, "dev_err" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x132a7a5b, "init_timer_key" },
	{ 0xdc1e1b7d, "device_create" },
	{ 0x4c1d0cd4, "__class_create" },
	{ 0xda72f6c6, "cdev_add" },
	{ 0xb1f57786, "cdev_init" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xdc798d37, "__mutex_init" },
	{ 0x5e0baa3a, "dev_set_drvdata" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x956a91ba, "gpio_get_value_cansleep" },
	{ 0xc8fd727e, "mod_timer" },
	{ 0x7d11c268, "jiffies" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x8949858b, "schedule_work" },
	{ 0x62b72b0d, "mutex_unlock" },
	{ 0xbc10dd97, "__put_user_4" },
	{ 0xe16b893b, "mutex_lock" },
	{ 0xc7ef0ce2, "class_destroy" },
	{ 0xcfad398d, "device_destroy" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x16808ecc, "cdev_del" },
	{ 0x37a0cba, "kfree" },
	{ 0xcca27eeb, "del_timer" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x11f447ce, "__gpio_to_irq" },
	{ 0xfe990052, "gpio_free" },
	{ 0x4205ad24, "cancel_work_sync" },
	{ 0x890208e3, "dev_get_drvdata" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1895E047F0E20E316C84EE7");
