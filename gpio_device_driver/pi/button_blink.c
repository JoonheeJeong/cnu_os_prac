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
    char pre_read_data = 0;
    int event_count = 0;

    while (1) {
	read(fd, &read_data, 1);
	if (pre_read_data == 0 && read_data == 1) {
	    printf("%10d: [BTN_R] PUSH\n", ++event_count);
	} else if (pre_read_data == 1 && read_data == 0) {
	    printf("%10d: [BTN_R] PULL\n", ++event_count);
	}
	pre_read_data = read_data;
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
