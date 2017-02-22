ifneq ($(KERNELRELEASE),)

obj-m :=gpout.o

else

KERNELDIR :=/home/mengqp/local/svn/platform/ePduHmi3352/kernel/linux-3.2.0-m3352

all:
	               make -C $(KERNELDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=/opt/arm-2011.03/bin/arm-none-linux-gnueabi-
clean:
	               rm -f *.o *.ko *.mod.o *.mod.c *.symvers

endif
