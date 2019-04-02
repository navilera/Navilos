/*
 * armcpu.h
 *
 *  Created on: Sep 22, 2018
 *      Author: maanu
 */

#ifndef LIB_ARMCPU_H_
#define LIB_ARMCPU_H_

void enable_irq(void);
void enable_fiq(void);
void disable_irq(void);
void disable_fiq(void);

#endif /* LIB_ARMCPU_H_ */
