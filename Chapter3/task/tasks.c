#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int task_init(void){
    struct task_struct *task;
    printk(KERN_INFO "Loading Module\n");
    for_each_process(task){
        printk(KERN_INFO "%s %d\n",task->comm,task_pid_nr(task));    
    }
    return 0;
}

void dfs_tasks(struct task_struct *this_task){
	struct task_struct *task;
	struct list_head *list;

	printk(KERN_INFO "%s %d\n",
			this_task->comm,
			task_pid_nr(this_task));

	list_for_each(list, &this_task->children) {
		task = list_entry(list, struct task_struct, sibling);

		dfs_tasks(task);
	}
}

void task_exit(void){
    printk(KERN_INFO "Removing Module\n");
}

module_init(task_init);
module_exit(task_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TASK Module");
MODULE_AUTHOR("SGG");

