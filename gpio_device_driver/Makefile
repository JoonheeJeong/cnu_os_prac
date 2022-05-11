obj-m := gpio_device_driver.o
KDIR := $(HOME)/rpi/linux
PWD := $(shell pwd)

default:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- \
	-C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
