/*** linan ***/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/printk.h>

static spinlock_t gpout_lock;

#define GPIO_TO_PIN(bank, gpio) (32 * (bank) + (gpio))


int gpio_out[] = {
	GPIO_TO_PIN(3,17),//beep_ctrl
	GPIO_TO_PIN(3,14),//jdq_ctrl1
	GPIO_TO_PIN(3,18),//jdq_ctrl2
	GPIO_TO_PIN(1,16),//led_gj
	GPIO_TO_PIN(1,17),//led_bak1
	GPIO_TO_PIN(1,18),//led_mp
	GPIO_TO_PIN(1,19),//led_bak2
	GPIO_TO_PIN(1,20),//led_run
	GPIO_TO_PIN(0,20)//led_boardrun
};




static int gpout_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "gpout open!\n");
    return 0;
}

static int gpout_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "gpout release!\n");
    return 0;
}

static ssize_t gpout_write(struct file *file, const char __user *data,
		size_t len, loff_t *ppos) {
   char wdata[2]={-1};
	int ret = -1;
	if (len != 2)
	{
	 	 printk(KERN_ALERT"Write count != 2\n");
	 	 return 0;
	}
	spin_lock(&gpout_lock);
	if (copy_from_user(wdata, data, len))
	{
		printk(KERN_ALERT " copy_from_user error !\n");
		goto _out;
	}
	/* printk(KERN_INFO "wdata[0] = %d, wdata[1] = %d\n",wdata[0],wdata[1]); */
    if(wdata[0] >= ARRAY_SIZE(gpio_out)){
		printk(KERN_ALERT " gpio info out of range !\n");
		goto _out;
   	}
	if(wdata[1] >= 1)
		wdata[1] = (char)1;
	else
		wdata[1] = (char)0;

	/* printk(KERN_INFO "set info %d gpio %d level %d\n",wdata[0] ,gpio_out[wdata[0]], wdata[1]); */
	gpio_direction_output((unsigned)gpio_out[(int)wdata[0]], (int)wdata[1]);
	gpio_set_value((unsigned)gpio_out[(int)wdata[0]], (int)wdata[1]);
	ret = len;
_out:
	spin_unlock(&gpout_lock);
    return ret;
}

// Kernel interface
static struct file_operations gpout_fops = {
    .owner           =   THIS_MODULE,
    .write           =   gpout_write,
    .open            =   gpout_open,
    .release         =   gpout_release,
};


#define DEV_NAME "gpout"
// driver interface
static struct class *gpout_class = NULL;
static struct device *gpout_device = NULL;
static dev_t gpout_devno;
static struct cdev gpout_cdev;

static int gpout_probe(struct platform_device *dev) {
    int ret = 0, err = 0;
    unsigned char i;
    printk(KERN_INFO "gpout probe!\n");

    // alloc character device number
    ret = alloc_chrdev_region(&gpout_devno, 0, 1, DEV_NAME);
    if (ret) {
        printk(KERN_ALERT " alloc_gpout_region failed!\n");
        goto PROBE_ERR;
    }
    printk(KERN_INFO " major:%d minor:%d\n", MAJOR(gpout_devno), MINOR(gpout_devno));

    cdev_init(&gpout_cdev, &gpout_fops);
    gpout_cdev.owner = THIS_MODULE;
    // add a character device
    err = cdev_add(&gpout_cdev, gpout_devno, 1);
    if (err) {
        printk(KERN_ALERT " cdev_add failed!\n");
        goto PROBE_ERR;
    }

    // create the device class
    gpout_class = class_create(THIS_MODULE, DEV_NAME);
    if (IS_ERR(gpout_class)) {
        printk(KERN_ALERT " class_create failed!\n");
        goto PROBE_ERR;
    }

    // create the device node in /dev
    gpout_device = device_create(gpout_class, NULL, gpout_devno,
        NULL, DEV_NAME);
    if (NULL == gpout_device) {
        printk(KERN_ALERT " device_create failed!\n");
        goto PROBE_ERR;
    }

	for (i = 0; i < ARRAY_SIZE(gpio_out); i++) {

		if(gpio_is_valid(gpio_out[i]))
		{
			int err = gpio_request(gpio_out[i], "gpout");
			if(err)
			{
				printk(KERN_ALERT " gpio_request %d failed!\n",gpio_out[i]);
			}
			else if( (i > 2) && (i <= (ARRAY_SIZE(gpio_out)-1)) )
			{
				gpio_direction_output(gpio_out[i], 1);
				gpio_set_value(gpio_out[i], 1);
			}
			else
			{
				gpio_direction_output(gpio_out[i], 0);
				gpio_set_value(gpio_out[i], 0);
			}

		}

	}

    printk(KERN_INFO " gpout probe ok!\n");
    return 0;

PROBE_ERR:
    if (err)
        cdev_del(&gpout_cdev);
    if (ret)
        unregister_chrdev_region(gpout_devno, 1);
    return -1;
}

static int gpout_remove (struct platform_device *dev) {
	unsigned char i;
    printk(KERN_INFO " gpout remove!\n");

	for(i = 0; i < ARRAY_SIZE(gpio_out); i++)
	{
		gpio_free(gpio_out[i]);
	}
    cdev_del(&gpout_cdev);
    unregister_chrdev_region(gpout_devno, 1);

    device_destroy(gpout_class, gpout_devno);
    class_destroy(gpout_class);
    return 0;
}

// platform_device and platform_driver must has a same name!
// or it will not work normally
static struct platform_driver gpout_platform_driver = {
    .probe  =   gpout_probe,
    .remove =   gpout_remove,
    .driver =   {
        .name   =   DEV_NAME,
        .owner  =   THIS_MODULE,
    },
};

struct platform_device *gpout_platform_device ;

static __init int gpout_init(void) {
    int ret = 0;
    printk(KERN_INFO "gpout init!\n");
	spin_lock_init(&gpout_lock);
    gpout_platform_device = platform_device_register_simple(DEV_NAME, -1, NULL, 0);
    if(IS_ERR( gpout_platform_device)) {

        printk(KERN_ALERT " platform_device_register failed!\n");
        return -EINVAL;
    }

    ret = platform_driver_register(&gpout_platform_driver);
    if (ret) {
        printk(KERN_ALERT " platform_driver_register failed!\n");
        return -EINVAL;
    }
    printk(KERN_INFO " gpout_init ok!\n");
    return ret;
}

static __exit void gpout_exit(void) {
    platform_driver_unregister(&gpout_platform_driver);
	platform_device_unregister(gpout_platform_device);
	printk(KERN_INFO "gpout exit!\n");
}

module_init(gpout_init);
module_exit(gpout_exit);

MODULE_AUTHOR("linan <linan_6688_cool@163.com>");
MODULE_DESCRIPTION("AM3352 GPIO OUT Driver");
MODULE_SUPPORTED_DEVICE(DEV_NAME);
MODULE_LICENSE("GPL");
MODULE_ALIAS("GPIO IRQ");
MODULE_VERSION("V1.0.0");
