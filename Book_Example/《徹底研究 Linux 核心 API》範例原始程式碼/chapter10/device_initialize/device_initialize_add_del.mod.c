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
	{ 0x4061a14b, "module_layout" },
	{ 0x4b7edd15, "device_add" },
	{ 0xff1b575f, "kobject_set_name" },
	{ 0x106b0af1, "device_initialize" },
	{ 0x4661e311, "__tracepoint_kmalloc" },
	{ 0xfd813ef7, "kmem_cache_alloc" },
	{ 0x5c43db65, "kmalloc_caches" },
	{ 0x1eb2af36, "__class_create" },
	{ 0x784ed09c, "register_chrdev" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x37a0cba, "kfree" },
	{ 0x999e8297, "vfree" },
	{ 0x9b6f4b74, "class_destroy" },
	{ 0x70184123, "device_del" },
	{ 0x65bc2119, "put_device" },
	{ 0x9ef749e2, "unregister_chrdev" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0xd6c963c, "copy_from_user" },
	{ 0x59733206, "module_put" },
	{ 0x7ecb001b, "__per_cpu_offset" },
	{ 0x26fd80b9, "per_cpu__cpu_number" },
	{ 0xb72397d5, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "74D0CF570BFC3CD6AA0B508");
