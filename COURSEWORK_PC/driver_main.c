/*=======================================*/
/* Simple driver for coursework on linux */
/*              MAIN_PART                */
/*=======================================*/
#include <linux/module.h> /* Needed by all modules */
#include <linux/moduleparam.h>
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h>   /* Needed for the macros */
#include <linux/stat.h>

extern void _off_cache(void);

// define zone
#define DRIVER_DESC "Simple driver for off/on caching on CPU;"
#define true 0x01
#define false 0x00

// kernel code info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antag0nist - R.A.Knyazyk <teorus2314@yandex.ru>");
MODULE_SUPPORTED_DEVICE("all");
MODULE_DESCRIPTION(DRIVER_DESC);

// input data zone
int off_on_flag = true;

// module_param zone (connect inputs with module)
module_param(off_on_flag, int, 0);

// initialize module
static int driver_init(void){
    printk(KERN_INFO "driver -> init_module();\n");
    printk(KERN_INFO "version (driver_main) -> 0.0.1\n");
    printk(KERN_INFO "off_on_flag = %d;\n", off_on_flag);

    // asm code
    __asm__("push   %rax\t\n"    
            "mov    %cr0,%rax\t\n"
            "or     $(1 << 30),%rax\n"
            "mov    %rax,%cr0\n"
            "wbinvd\n"
            "pop    %rax"
    );

    /*
            ";Step 2 - Disable speculative accesses\n"
            "xor eax, eax\n"
            "xor edx, edx\n"
            "mov ecx, 0x2FFH\n"
            "wrmsr\n"
    */

    printk(KERN_INFO "driver -> end init_module();\n");
    return 0;
}

// cleanup all
static void driver_cleanup(void){
    printk(KERN_INFO "driver -> clean_module();\n");

    // warning: work or not
    __asm__("push   %rax\n"
            "mov    %cr0,%rax\n"
            "and     $~(1 << 30),%rax\n"
            "mov    %rax,%cr0\n"
            "wbinvd\n"
            "pop    %rax"
    );

    printk(KERN_INFO "driver -> restore_cache();\n");
    return;
}

// rename module func
module_init(driver_init);
module_exit(driver_cleanup);