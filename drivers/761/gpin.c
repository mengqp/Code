/*** linan ***/

#include <linux/module.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/gpio_keys.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>  
#include <linux/uaccess.h>

struct gpio_button_data {
	struct gpio_keys_button *button;
	struct timer_list timer;
	struct work_struct work;
	int timer_debounce;	/* in msecs */
	bool disabled;
};

struct gpio_keys_drvdata {
	unsigned int n_buttons;
	int (*enable)(struct device *dev);
	void (*disable)(struct device *dev);
	struct gpio_button_data data[0];
};

struct mutex disable_lock;

int gpio_level[7] = {0};

#define	GPIO_GETMU	_IOWR('G', 0x3A, int)
#define	GPIO_GETOS	_IOWR('G', 0x3B, int)							
#define	GPIO_GETBF	_IOWR('G', 0x3C, int)
#define	GPIO_GETBU	_IOWR('G', 0x3D, int)
#define	GPIO_GETMW	_IOWR('G', 0x3E, int)
#define	GPIO_GETBW	_IOWR('G', 0x3F, int)
#define	GPIO_GETGJ	_IOWR('G', 0x39, int) //告警复位手动信号



static void gpio_keys_report_event(struct gpio_button_data *bdata)
{
	struct gpio_keys_button *button = bdata->button;
	int num = button->code;
	
	
	int state = gpio_get_value_cansleep(button->gpio) ? 1 : 0;
	
	mutex_lock(&disable_lock);
	gpio_level[num] = state;
	
	mutex_unlock(&disable_lock);
	//printk("***********linan tset num  %d  level = %d \n",num, state);
}

static void gpio_keys_work_func(struct work_struct *work)
{
	struct gpio_button_data *bdata =
		container_of(work, struct gpio_button_data, work);

	gpio_keys_report_event(bdata);
}

static void gpio_keys_timer(unsigned long _data)
{
	struct gpio_button_data *data = (struct gpio_button_data *)_data;

	schedule_work(&data->work);
}

static irqreturn_t gpio_keys_isr(int irq, void *dev_id)
{
	struct gpio_button_data *bdata = dev_id;
	struct gpio_keys_button *button = bdata->button;

	BUG_ON(irq != gpio_to_irq(button->gpio));

	if (bdata->timer_debounce)
		mod_timer(&bdata->timer,
			jiffies + msecs_to_jiffies(bdata->timer_debounce));
	else
		schedule_work(&bdata->work);

	return IRQ_HANDLED;
}

static int __devinit gpio_keys_setup_key(struct platform_device *pdev,
					 struct gpio_button_data *bdata,
					 struct gpio_keys_button *button)
{
	const char *desc = button->desc ? button->desc : "gpio_keys";
	struct device *dev = &pdev->dev;
	unsigned long irqflags;
	int irq, error;

	setup_timer(&bdata->timer, gpio_keys_timer, (unsigned long)bdata);
	INIT_WORK(&bdata->work, gpio_keys_work_func);

	error = gpio_request(button->gpio, desc);
	if (error < 0) {
		dev_err(dev, "failed to request GPIO %d, error %d\n",
			button->gpio, error);
		goto fail2;
	}

	error = gpio_direction_input(button->gpio);
	if (error < 0) {
		dev_err(dev, "failed to configure"
			" direction for GPIO %d, error %d\n",
			button->gpio, error);
		goto fail3;
	}

	if (button->debounce_interval) {
		bdata->timer_debounce = button->debounce_interval;
	}

	irq = gpio_to_irq(button->gpio);
	if (irq < 0) {
		error = irq;
		dev_err(dev, "Unable to get irq number for GPIO %d, error %d\n",
			button->gpio, error);
		goto fail3;
	}

	irqflags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	

	error = request_threaded_irq(irq, NULL, gpio_keys_isr, irqflags, desc, bdata);
	if (error < 0) {
		dev_err(dev, "Unable to claim irq %d; error %d\n",
			irq, error);
		goto fail3;
	}

	return 0;

fail3:
	gpio_free(button->gpio);
fail2:
	return error;
}

static int gpin_open(struct inode *inode, struct file *file) {  
    printk(KERN_INFO "gpin open!\n");  
    return 0;  
}  
  
static int gpin_release(struct inode *inode, struct file *file) {  
    printk(KERN_INFO "gpin release!\n");  
    return 0;  
}  
  
static long  gpin_ioctl(struct file *file, unsigned int cmd,
						unsigned long arg) { 
  int ret = 0;
  switch (cmd) {
  	case GPIO_GETMU:
		mutex_lock(&disable_lock);
	    put_user(gpio_level[0], (int __user *)arg);
		mutex_unlock(&disable_lock);
		break;
	case GPIO_GETOS:
		mutex_lock(&disable_lock);
		put_user(gpio_level[1], (int __user *)arg);
		mutex_unlock(&disable_lock);
		break;
	case GPIO_GETBF:
		mutex_lock(&disable_lock);
		put_user(gpio_level[2], (int __user *)arg);
		mutex_unlock(&disable_lock);
		break;
	case GPIO_GETBU:
		mutex_lock(&disable_lock);
		put_user(gpio_level[3], (int __user *)arg);
		mutex_unlock(&disable_lock);
		break;
	case GPIO_GETMW:
		mutex_lock(&disable_lock);
		put_user(gpio_level[4], (int __user *)arg);
		mutex_unlock(&disable_lock);
		break;
	case GPIO_GETBW:
		mutex_lock(&disable_lock);
		put_user(gpio_level[5], (int __user *)arg);
		mutex_unlock(&disable_lock);
		break;
	case GPIO_GETGJ:
		mutex_lock(&disable_lock);
		put_user(gpio_level[6], (int __user *)arg);
		mutex_unlock(&disable_lock);
		break;
	default:
		ret = -ENOTTY;	
  	}
  return ret;
}

  
// Kernel interface  
static struct file_operations gpin_fops = {  
    .owner               =   THIS_MODULE,  
    .unlocked_ioctl      =   gpin_ioctl,  
    .open                =   gpin_open,  
    .release             =   gpin_release,  
};  
  
  
#define DEV_NAME "gpin"  
// driver interface  
static struct class *gpin_class = NULL;  
static struct device *gpin_device = NULL;  
static dev_t gpin_devno;  
static struct cdev gpin_cdev;  
  
static int gpin_probe(struct platform_device *pdev) {  
    int  err = 0;  
    int i; 
	struct gpio_keys_platform_data *pdata = pdev->dev.platform_data;
	struct gpio_keys_drvdata *ddata;
	
    printk(KERN_INFO "gpin probe!\n");  
	
	ddata = kzalloc(sizeof(struct gpio_keys_drvdata) +
			pdata->nbuttons * sizeof(struct gpio_button_data),
			GFP_KERNEL);

	ddata->n_buttons = pdata->nbuttons;
	ddata->enable = pdata->enable;
	ddata->disable = pdata->disable;
 
	platform_set_drvdata(pdev, ddata);
	for (i = 0; i < pdata->nbuttons; i++) {
		struct gpio_keys_button *button = &pdata->buttons[i];
		struct gpio_button_data *bdata = &ddata->data[i];
		bdata->button = button;
		err = gpio_keys_setup_key(pdev, bdata, button);
				if (err)
					goto fail1;

		
	} 
	mutex_init(&disable_lock);
    // alloc character device number  
    err = alloc_chrdev_region(&gpin_devno, 0, 1, DEV_NAME);  
    if (err) {  
        printk(KERN_ALERT " alloc_gpin_region failed!\n");  
        goto fail1;  
    }  
    printk(KERN_INFO " major:%d minor:%d\n", MAJOR(gpin_devno), MINOR(gpin_devno));  
      
    cdev_init(&gpin_cdev, &gpin_fops);  
    gpin_cdev.owner = THIS_MODULE;  
    // add a character device  
    err = cdev_add(&gpin_cdev, gpin_devno, 1);  
    if (err) {  
        printk(KERN_ALERT " cdev_add failed!\n");  
        goto fail2;  
    }  
      
    // create the device class  
    gpin_class = class_create(THIS_MODULE, DEV_NAME);  
    if (IS_ERR(gpin_class)) {  
        printk(KERN_ALERT " class_create failed!\n");  
        goto fail3;  
    }  
      
    // create the device node in /dev  
    gpin_device = device_create(gpin_class, NULL, gpin_devno,  
        NULL, DEV_NAME);  
    if (NULL == gpin_device) {  
        printk(KERN_ALERT " device_create failed!\n");  
        goto fail3;  
    }  
	
		/* get current state of buttons */
	for (i = 0; i < pdata->nbuttons; i++)
		gpio_keys_report_event(&ddata->data[i]);
    printk(KERN_INFO " gpin probe ok!\n");  
    return 0; 

fail3: 
        cdev_del(&gpin_cdev);  
fail2:  
        unregister_chrdev_region(gpin_devno, 1);
fail1:
 	while (--i >= 0) {
		free_irq(gpio_to_irq(pdata->buttons[i].gpio), &ddata->data[i]);
		if (ddata->data[i].timer_debounce)
			del_timer_sync(&ddata->data[i].timer);
		cancel_work_sync(&ddata->data[i].work);
		gpio_free(pdata->buttons[i].gpio);
	} 
	platform_set_drvdata(pdev, NULL);
    return -1;  
}  
  
static int gpin_remove (struct platform_device *pdev) { 
   
	struct gpio_keys_drvdata *ddata = platform_get_drvdata(pdev);
	int i;

	printk(KERN_INFO " gpin remove!\n"); 

	for (i = 0; i < ddata->n_buttons; i++) {
		int irq = gpio_to_irq(ddata->data[i].button->gpio);
		free_irq(irq, &ddata->data[i]);
		if (ddata->data[i].timer_debounce)
			del_timer_sync(&ddata->data[i].timer);
		cancel_work_sync(&ddata->data[i].work);
		gpio_free(ddata->data[i].button->gpio);
	}
	/*
	 * If we had no platform_data, we allocated buttons dynamically, and
	 * must free them here. ddata->data[0].button is the pointer to the
	 * beginning of the allocated array.
	 */
	if (!pdev->dev.platform_data)
		kfree(ddata->data[0].button);

	kfree(ddata);
    cdev_del(&gpin_cdev);  
    unregister_chrdev_region(gpin_devno, 1);  
      
    device_destroy(gpin_class, gpin_devno);  
    class_destroy(gpin_class);  
    return 0;  
}  
  
// platform_device and platform_driver must has a same name!  
// or it will not work normally  
static struct platform_driver gpin_platform_driver = {  
    .probe  =   gpin_probe,  
    .remove =   gpin_remove,  
    .driver =   {  
        .name   =   DEV_NAME,  
        .owner  =   THIS_MODULE,  
    },  
};  
  
struct platform_device *gpin_platform_device ; 
  
static __init int gpin_init(void) {  
    int ret = 0;  
    printk(KERN_INFO "gpin init!\n");  
  
    ret = platform_driver_register(&gpin_platform_driver);  
    if (ret) {  
        printk(KERN_ALERT " platform_driver_register failed!\n");  
        return -EINVAL;  
    }  
    printk(KERN_INFO " gpin_init ok!\n");  
    return ret;  
}  
  
static __exit void gpin_exit(void) {   
    platform_driver_unregister(&gpin_platform_driver); 
	platform_device_unregister(gpin_platform_device);
	printk(KERN_INFO "gpin exit!\n");  
}  
  
module_init(gpin_init);  
module_exit(gpin_exit);

MODULE_AUTHOR("linan <linan_6688_cool@163.com>");
MODULE_DESCRIPTION("AM3352 GPIO OUT Driver");
MODULE_SUPPORTED_DEVICE(DEV_NAME);
MODULE_LICENSE("GPL");
MODULE_ALIAS("GPIO IRQ");
MODULE_VERSION("V1.0.0");



