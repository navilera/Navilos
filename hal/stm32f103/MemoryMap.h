#ifndef _HAL_MEMORYMAP_H_
#define _HAL_MEMORYMAP_H_

/*
 * eFlash
 *
 * 0  ~ 19 page (20KB) : Loader		-> 0x08000000 ~ 0x08004FFF
 * 20 ~ 62 page (43KB) : Main FW	-> 0x08005000 ~ 0x0800FBFF
 * 63 page      (1KB)  : Keymap		-> 0x0800FC00
 */

extern uint32_t __bss_end__;

#define TASK_STACK_START    ((uint32_t)&__bss_end__)
#define USR_TASK_STACK_SIZE (2 * 1024)
#define TASK_STACK_SIZE     (USR_TASK_STACK_SIZE * 3)

#define EFLASH_TOTALNUM		64
#define EFLASH_START        0x08000000
#define EFLASH_PAGESIZE     0x400
#define EFLASH_BADDR(X)     (EFLASH_START + EFLASH_PAGESIZE * (X))

#define MAIN_FW_PAGENUM	 	 20
#define MAIN_FW_FLASH_SIZE	 43
#define MAIN_FW_ENTRY_OFFSET (MAIN_FW_PAGENUM * EFLASH_PAGESIZE)
#define MAIN_FW_BADDR        EFLASH_BADDR(MAIN_FW_PAGENUM)

#define KEYMAP_PAGENUM      (EFLASH_TOTALNUM - 1)  				/* last page of eFlash */
#define KEYMAP_BADDR        EFLASH_BADDR(KEYMAP_PAGENUM)

#endif /*_HAL_MEMORYMAP_H_ */
