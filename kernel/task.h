/*
 * task.h
 *
 *  Created on: Oct 22, 2018
 *      Author: maanu
 */

#ifndef KERNEL_TASK_H_
#define KERNEL_TASK_H_

#define NOT_ENOUGH_TASK_NUM     0xFFFFFFFF

typedef struct KernelTaskContext_t
{
    uint32_t spsr;
    uint32_t r0_r12[13];
    uint32_t pc;
} KernelTaskContext_t;

typedef struct KernelTcb_t
{
    uint32_t sp;
    uint8_t* stack_base;
} KernelTcb_t;

typedef void (*KernelTaskFunc_t)(void);

void     Kernel_task_init(void);
void     Kernel_task_start(void);
uint32_t Kernel_task_create(KernelTaskFunc_t startFunc);
void     Kernel_task_scheduler(void);
uint32_t Kernel_task_get_current_task_id(void);

#endif /* KERNEL_TASK_H_ */
