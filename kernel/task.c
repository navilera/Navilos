/*
 * task.c
 *
 *  Created on: Oct 22, 2018
 *      Author: maanu
 */


#include "stdint.h"
#include "stdbool.h"

#include "ARMv7AR.h"
#include "task.h"

static KernelTcb_t  sFree_task_pool[MAX_TASK_NUM];
static uint32_t     sAllocated_tcb_index;

void Kernel_task_init(void)
{
    sAllocated_tcb_index = 0;

    for(uint32_t i = 0 ; i < MAX_TASK_NUM ; i++)
    {
        sFree_task_pool[i].spsr = ARM_MODE_BIT_SYS;
        sFree_task_pool[i].lr = 0;
        sFree_task_pool[i].pc = 0;

        sFree_task_pool[i].stack_base = (uint8_t*)(TASK_STACK_START + (i * USR_TASK_STACK_SIZE));
        sFree_task_pool[i].sp = (uint32_t)sFree_task_pool[i].stack_base + USR_TASK_STACK_SIZE - 4;
    }
}

uint32_t Kernel_task_create(KernelTaskFunc_t startFunc)
{
    KernelTcb_t* new_tcb = &sFree_task_pool[sAllocated_tcb_index++];

    if (sAllocated_tcb_index > MAX_TASK_NUM)
    {
        return NOT_ENOUGH_TASK_NUM;
    }

    new_tcb->pc = (uint32_t)startFunc;

    return (sAllocated_tcb_index - 1);
}
