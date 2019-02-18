/*Name : Raj Lavingia
Date : 2/17/2019
References : https://www.tldp.org/LDP/lkmpg/2.6/html/x323.html
https://stackoverflow.com/questions/10812858/how-to-use-timers-in-linux-kernel-device-drivers
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

//Variables Declared
int time_difference = 500,my_count;
struct timer_list raj_timer;
char *set_name = "Raj";

//User can define this parameters
module_param(set_name, charp , S_IRUSR | S_IWUSR);
module_param(time_difference, int , S_IRUSR | S_IWUSR);

//Modinfo details
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raj Lavingia");
MODULE_DESCRIPTION("Timer for kernel");

//Interuppt function
void _interrupt_Timer(unsigned long data)
{
    mod_timer( &raj_timer, jiffies + msecs_to_jiffies(time_difference));
    my_count++;
    printk(KERN_DEFAULT "One step complete\n");
    printk(KERN_DEFAULT "Name defined %s Counter value: %d\n", set_name,my_count);
}

//Main
static int __init initialization(void)
{
   
    setup_timer(&raj_timer,_interrupt_Timer, 0);
    mod_timer( &raj_timer, jiffies + msecs_to_jiffies(time_difference));

    return 0;
}

//Delete Kernel Module
static void __exit removing(void)
{
    del_timer(&raj_timer);
    printk(KERN_DEFAULT "Module deleted\n");
}

																																																																module_init(initialization);
																																																									module_exit(removing);
