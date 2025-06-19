#include <linux/kernel.h>
#include <linux/module.h>

#define MSG_WELCOME "Hola Kernel!! Soy el modulo de Coredumpers\n"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo del equipo Coredumpers");
MODULE_AUTHOR("Priscila, Pablo y Emiliano");

int module_i(void) {

  for (int i = 3; i > 0; i--) {
    printk(KERN_INFO "Bienvenida en: ");
    printk(KERN_INFO "%d\n", i + 1);
  }
  printk(KERN_INFO MSG_WELCOME);
  printk(KERN_INFO "Somos Emiliano, Priscila y Pablo.");
  return 0;
}

void module_e(void) { printk(KERN_INFO "Cahu Kernel!.\n"); }

module_init(module_i);
module_exit(module_e);
