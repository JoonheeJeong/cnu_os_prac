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
    char write_data;
    while (1) {
	printf("LED ON\n");
	write_data = 1;
	write(fd, &write_data, 1);
	sleep(1);

	printf("LED OFF\n");
	write_data = 0;
	write(fd, &write_data, 1);
	sleep(1);
    }
}

int main()
{
    printf("Test GPIO\n");

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
