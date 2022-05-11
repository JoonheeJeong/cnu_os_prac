#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/uaccess.h> // copy_to/from_user
#include "gpio_device_driver.h"

static int __init gpio_init(void);
static void __exit gpio_exit(void);

static int gpio_open(struct inode *inode, struct file *filp);
static int gpio_release(struct inode *inode, struct file *filp);
static ssize_t gpio_read(struct file *filp, 
		char *buf, size_t len, loff_t *off);
static ssize_t gpio_write(struct file *filp,
		const char *buf, size_t len, loff_t *off);

static struct file_operations gpio_fops = {
    .owner	= THIS_MODULE,
    .open	= gpio_open,
    .release	= gpio_release,
    .read	= gpio_read,
    .write	= gpio_write,
};

static int gpio_open(struct inode *inode, struct file *filp)
{
    if (gpio_request(LED_R, "led_red") > 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "LED_R OPEN COMPLETE\n");
	gpio_direction_output(LED_R, 1);
    }

    if (gpio_request(BTN_R, "btn_red") > 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "BTN_R OPEN COMPLETE\n");
	gpio_direction_input(BTN_R);
    }
    return 0;
}

static int gpio_release(struct inode *inode, struct file *filp)
{
    gpio_free(BTN_R);
    gpio_free(LED_R);
    return 0;
}

static ssize_t gpio_read(struct file *filp, 
		char *buf, size_t len, loff_t *off)
{
    char input = gpio_get_value(BTN_R);
    if (input == 1)
	printk(KERN_INFO "BTN_R PUSH\n");
    else if (input == 0)
	printk(KERN_INFO "BTN_R PULL\n");
    else
	printk(KERN_ERR "ERROR: unknown user input");

    if (copy_to_user(buf, &input, len) > 0)
	printk(KERN_ERR "ERROR: copy_to_user\n");
    else
	printk(KERN_INFO "READ GPIO\n");

    return 0;
}

static ssize_t gpio_write(struct file *filp,
		const char *buf, size_t len, loff_t *off)
{
    char temp;
    if (copy_from_user(&temp, buf, len) > 0)
	printk(KERN_ERR "ERROR: copy_from_user\n");
    else
	printk(KERN_INFO "WRITE GPIO\n");

    if (temp == 1)
	gpio_set_value(LED_R, 1);
    else if (temp == 0)
	gpio_set_value(LED_R, 0);
    else
	printk(KERN_ERR "ERROR: unknown user input");
    return len;
}

static int __init gpio_init(void)
{
    if (register_chrdev(DEV_GPIO_MAJOR, DEV_GPIO_NAME, &gpio_fops) < 0) {
	printk(KERN_ERR "ERROR: cannot allocate Major %d for %s\n", 
	    DEV_GPIO_MAJOR, DEV_GPIO_NAME);
	return -EBUSY;
    }
    printk(KERN_INFO "Insert Device Driver %s(Major:%d)\n", 
	DEV_GPIO_NAME, DEV_GPIO_MAJOR);
    return 0;
}

static void __exit gpio_exit(void)
{
    gpio_free(BTN_R);
    gpio_free(LED_R);
    unregister_chrdev(DEV_GPIO_MAJOR, DEV_GPIO_NAME);
    printk(KERN_INFO "Remove Device Driver ... Done!\n");
}

module_init(gpio_init);
module_exit(gpio_exit);
MODULE_LICENSE("GPL");
