#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int __init hello_module_init(void)
{
    printk("Hello, module!\n");
    return 0;
}

void __exit hello_module_exit(void)
{
    printk("Bye, module!\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);
MODULE_LICENSE("GPL");
