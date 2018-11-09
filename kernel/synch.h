/*
 * synch.h
 *
 *  Created on: Nov 8, 2018
 *      Author: maanu
 */

#ifndef KERNEL_SYNCH_H_
#define KERNEL_SYNCH_H_

void Kernel_sem_init(int32_t max);
bool Kernel_sem_test(void);
void Kernel_sem_release(void);

#endif /* KERNEL_SYNCH_H_ */
