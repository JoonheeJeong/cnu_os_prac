#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/kdev_t.h>
#include "gpio_device_driver.h"

void blink_led(int fd)
{
    char read_data = 0;
    char input_r = 0;
    char input_g = 0;
    char input_w = 0;
    char input_y = 0;
    char pre_read_data = 0;
    char pre_input_r = 0;
    char pre_input_g = 0;
    char pre_input_w = 0;
    char pre_input_y = 0;
    unsigned long event_count = 0;

    while (1) {
	read(fd, &read_data, 1);
	input_r = read_data & 1;
	input_g = (read_data & 2) >> 1;
	input_w = (read_data & 4) >> 2;
	input_y = (read_data & 8) >> 3;
	if (pre_input_r == 0 && input_r == 1) {
	    printf("%10d: [BTN_R] PUSH\n", ++event_count);
	} else if (pre_input_r == 1 && input_r == 0) {
	    printf("%10d: [BTN_R] PULL\n", ++event_count);
	}
	if (pre_input_g == 0 && input_g == 1) {
	    printf("%10d: [BTN_G] PUSH\n", ++event_count);
	} else if (pre_input_g == 1 && input_g == 0) {
	    printf("%10d: [BTN_G] PULL\n", ++event_count);
	}
	if (pre_input_w == 0 && input_w == 1) {
	    printf("%10d: [BTN_W] PUSH\n", ++event_count);
	} else if (pre_input_w == 1 && input_w == 0) {
	    printf("%10d: [BTN_W] PULL\n", ++event_count);
	}
	if (pre_input_y == 0 && input_y == 1) {
	    printf("%10d: [BTN_Y] PUSH\n", ++event_count);
	} else if (pre_input_y == 1 && input_y == 0) {
	    printf("%10d: [BTN_Y] PULL\n", ++event_count);
	}
	pre_read_data = read_data;
	pre_input_r = input_r;
	pre_input_g = input_g;
	pre_input_w = input_w;
	pre_input_y = input_y;
	write(fd, &read_data, 1);
	usleep(100000); // delay by 0.1s to prevent duplicate inputs
    }
}

int main()
{
    printf("Read Button and Output to the RED LED\n");

    mknod(DEV_FILE_NAME, (S_IRWXU|S_IRWXG|S_IFCHR), MKDEV(DEV_GPIO_MAJOR, 0));
    int fd = open(DEV_FILE_NAME, O_RDWR|O_NONBLOCK);
    if (fd < 0) {
	fprintf(stderr, "Error: Cannot open GPIO Driver\n");
	exit(1);
    }

    blink_led(fd);
    close(fd);
    return 0;
}
