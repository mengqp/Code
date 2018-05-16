ifneq ($(KERNELRELEASE),)

obj-m :=gpin.o

else

KERNELDIR :=/home/mengqp/local/svn/platform/em761/kernel/linux-3.2.0-psp04.06.00.11-m3352

all:
	               make -C $(KERNELDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=/opt/arm-2011.03/bin/arm-none-linux-gnueabi-
clean:
	               rm -f *.o *.ko *.mod.o *.mod.c *.symvers

endif
