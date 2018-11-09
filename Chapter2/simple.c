#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday{
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);
struct birthday *person;
    
/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");
    person = kmalloc(sizeof(*person),GFP_KERNEL);
    person->day = 2;
    person->month = 8;
    person->year = 1995;
    INIT_LIST_HEAD(&person->list);

    list_add_tail(&person->list,&birthday_list);

    struct birthday *ptr;
    
    list_for_each_entry(ptr,&birthday_list,list){
        printk(KERN_INFO "%d, %d, %d", ptr->month,ptr->day,ptr->year);
    }

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr,next,&birthday_list,list){
        list_del(&ptr->list);
        kfree(ptr);
    }
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

