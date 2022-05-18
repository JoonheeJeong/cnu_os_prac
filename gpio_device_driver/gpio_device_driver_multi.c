#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/uaccess.h> // copy_to/from_user
#include "gpio_device_driver.h"

#define LED_R	17
#define LED_G	27
#define LED_W	22
#define LED_Y	23
#define BTN_R	13
#define BTN_G	19 // BLUE
#define BTN_W	26
#define BTN_Y	24

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
    if (gpio_request(LED_R, "led_red") != 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "LED_R OPEN COMPLETE\n");
	gpio_direction_output(LED_R, 0);
    }

    if (gpio_request(BTN_R, "btn_red") != 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "BTN_R OPEN COMPLETE\n");
	gpio_direction_input(BTN_R);
    }

    if (gpio_request(LED_G, "led_green") != 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "LED_G OPEN COMPLETE\n");
	gpio_direction_output(LED_G, 0);
    }

    if (gpio_request(BTN_G, "btn_green") != 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "BTN_G OPEN COMPLETE\n");
	gpio_direction_input(BTN_G);
    }

    if (gpio_request(LED_W, "led_white") != 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "LED_W OPEN COMPLETE\n");
	gpio_direction_output(LED_W, 0);
    }

    if (gpio_request(BTN_W, "btn_white") != 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "BTN_W OPEN COMPLETE\n");
	gpio_direction_input(BTN_W);
    }

    if (gpio_request(LED_Y, "led_yellow") != 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "LED_Y OPEN COMPLETE\n");
	gpio_direction_output(LED_Y, 0);
    }

    if (gpio_request(BTN_Y, "btn_yellow") != 0) {
	printk(KERN_ERR "ERROR: gpio_request\n");
	return -1;
    } else {
	printk(KERN_INFO "BTN_Y OPEN COMPLETE\n");
	gpio_direction_input(BTN_Y);
    }
    return 0;
}

static int gpio_release(struct inode *inode, struct file *filp)
{
    gpio_free(BTN_Y);
    gpio_free(LED_Y);
    gpio_free(BTN_W);
    gpio_free(LED_W);
    gpio_free(BTN_G);
    gpio_free(LED_G);
    gpio_free(BTN_R);
    gpio_free(LED_R);
    return 0;
}

static ssize_t gpio_read(struct file *filp, 
		char *buf, size_t len, loff_t *off)
{
    char input_r = gpio_get_value(BTN_R);
    char input_g = gpio_get_value(BTN_G);
    char input_w = gpio_get_value(BTN_W);
    char input_y = gpio_get_value(BTN_Y);
    char input = input_r | input_g << 1 | input_w << 2 | input_y << 3;

    if (copy_to_user(buf, &input, len) != 0) {
	printk(KERN_ERR "ERROR: copy_to_user\n");
	return -1;
    }

    //printk(KERN_INFO "READ GPIO\n");
    return len;
}

static ssize_t gpio_write(struct file *filp,
		const char *buf, size_t len, loff_t *off)
{
    char temp, output_r, output_g, output_w, output_y;

    if (copy_from_user(&temp, buf, len) > 0) {
	printk(KERN_ERR "ERROR: copy_from_user\n");
	return -1;
    }
    
    output_r = temp & 1;
    output_g = (temp & 2) >> 1;
    output_w = (temp & 4) >> 2;
    output_y = (temp & 8) >> 3;

    gpio_set_value(LED_R, output_r);
    gpio_set_value(LED_G, output_g);
    gpio_set_value(LED_W, output_w);
    gpio_set_value(LED_Y, output_y);

    //printk(KERN_INFO "WRITE GPIO\n");
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
    gpio_free(BTN_Y);
    gpio_free(LED_Y);
    gpio_free(BTN_W);
    gpio_free(LED_W);
    gpio_free(BTN_G);
    gpio_free(LED_G);
    gpio_free(BTN_R);
    gpio_free(LED_R);
    unregister_chrdev(DEV_GPIO_MAJOR, DEV_GPIO_NAME);
    printk(KERN_INFO "Remove Device Driver ... Done!\n");
}

module_init(gpio_init);
module_exit(gpio_exit);
MODULE_LICENSE("GPL");
