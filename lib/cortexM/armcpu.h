/*
 * armcpu.h
 *
 *  Created on: Sep 22, 2018
 *      Author: maanu
 */

#ifndef LIB_ARMCPU_H_
#define LIB_ARMCPU_H_

#include "stdint.h"

#define __CLZ             __builtin_clz

void enable_irq(void);
void enable_fiq(void);
void disable_irq(void);
void disable_fiq(void);

__inline void set_CONTROL(uint32_t control)
{
  __asm__ ("MSR control, %0" : : "r" (control) : "memory");
}

#endif /* LIB_ARMCPU_H_ */
