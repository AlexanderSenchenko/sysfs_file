#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>

#define DEVICE_NAME "sysfs"
#define MSG_LEN 80

static ssize_t sysfs_show(struct kobject*, struct kobj_attribute*, char*);
static ssize_t sysfs_store(struct kobject*, struct kobj_attribute*,
                           const char*, size_t);

static struct kobject *sysfs_kobj;

static const struct kobj_attribute sysfs_kobj_attr =
        __ATTR(sysfs, S_IRUGO | S_IWUSR, sysfs_show, sysfs_store);

static char msg[MSG_LEN];
static int size_msg;

int __init sysfs_init(void)
{
  int sysfs_file;
  printk(KERN_INFO "Trying to create /proc/%s:\n", DEVICE_NAME);

  sysfs_kobj = kobject_create_and_add("sysfs", NULL);

  sysfs_file = sysfs_create_file(sysfs_kobj, &sysfs_kobj_attr.attr);
  if (sysfs_file) {
    kobject_put(sysfs_kobj);
    return sysfs_file;
  }

  memset(&msg, 0, MSG_LEN);
  size_msg = sprintf(msg, "%s\n", "Hello!\n");

  return 0;
}

void __exit sysfs_exit(void)
{
  sysfs_remove_file(sysfs_kobj, &sysfs_kobj_attr.attr);
  kobject_put(sysfs_kobj);
  printk(KERN_INFO "/proc/%s removed\n", DEVICE_NAME);
}

ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr,
                   char *buf)
{
  return snprintf(buf, size_msg, "%s\n", msg);
}

ssize_t sysfs_store(struct kobject *kobj,
				            struct kobj_attribute *attr,
				            const char *buf, size_t size)
{
  // memset(&msg, 0, MSG_LEN);

  // if (size > MSG_LEN)
  //   size_msg = snprintf(msg, MSG_LEN, "%s\n", buf);
  // else
  //   size_msg = snprintf(msg, size, "%s\n", buf);

  // return size_msg;
  return 0;
}

module_init(sysfs_init);
module_exit(sysfs_exit);

MODULE_LICENSE("GPL");