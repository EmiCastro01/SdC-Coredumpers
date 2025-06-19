// drv_coredumpers.c
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "coredumpers"
#define CLASS_NAME "core"

static dev_t dev_num;
static struct class *core_class;
static struct cdev core_cdev;

// buffer circular simple
enum { BUF_SIZE = 4096 };
static char kbuf[BUF_SIZE];
static size_t wr_pos = 0, rd_pos = 0;
static DEFINE_MUTEX(buf_mutex);

static int dev_open(struct inode *inode, struct file *file) { return 0; }
static int dev_release(struct inode *inode, struct file *file) { return 0; }

static ssize_t dev_read(struct file *file, char __user *buf, size_t len,
                        loff_t *off) {
  size_t avail;
  mutex_lock(&buf_mutex);
  avail = (wr_pos + BUF_SIZE - rd_pos) % BUF_SIZE;
  if (len > avail)
    len = avail;
  if (len == 0) {
    mutex_unlock(&buf_mutex);
    return 0;
  }
  if (rd_pos + len <= BUF_SIZE) {
    if (copy_to_user(buf, kbuf + rd_pos, len))
      len = -EFAULT;
  } else {
    size_t first = BUF_SIZE - rd_pos;
    if (copy_to_user(buf, kbuf + rd_pos, first)) {
      len = -EFAULT;
      goto out;
    }
    if (copy_to_user(buf + first, kbuf, len - first))
      len = -EFAULT;
  }
  rd_pos = (rd_pos + len) % BUF_SIZE;
out:
  mutex_unlock(&buf_mutex);
  return len;
}

static ssize_t dev_write(struct file *file, const char __user *buf, size_t len,
                         loff_t *off) {
  if (len > BUF_SIZE)
    return -EINVAL;
  mutex_lock(&buf_mutex);
  if (wr_pos + len <= BUF_SIZE) {
    if (copy_from_user(kbuf + wr_pos, buf, len))
      len = -EFAULT;
  } else {
    size_t first = BUF_SIZE - wr_pos;
    if (copy_from_user(kbuf + wr_pos, buf, first)) {
      len = -EFAULT;
      goto outw;
    }
    if (copy_from_user(kbuf, buf + first, len - first))
      len = -EFAULT;
  }
  wr_pos = (wr_pos + len) % BUF_SIZE;
outw:
  mutex_unlock(&buf_mutex);
  return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .release = dev_release,
    .read = dev_read,
    .write = dev_write,
};

static int __init core_init(void) {
  alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
  cdev_init(&core_cdev, &fops);
  cdev_add(&core_cdev, dev_num, 1);
  core_class = class_create(CLASS_NAME);
  device_create(core_class, NULL, dev_num, NULL, DEVICE_NAME);
  mutex_init(&buf_mutex);
  pr_info("coredumpers driver loaded\n");
  return 0;
}
static void __exit core_exit(void) {
  device_destroy(core_class, dev_num);
  class_destroy(core_class);
  cdev_del(&core_cdev);
  unregister_chrdev_region(dev_num, 1);
  pr_info("coredumpers driver unloaded\n");
}

MODULE_LICENSE("GPL");
module_init(core_init);
module_exit(core_exit);
