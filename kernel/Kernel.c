/*
 * Kernel.c
 *
 *  Created on: Oct 28, 2018
 *      Author: maanu
 */


#include "stdint.h"
#include "stdbool.h"

#include "Kernel.h"


void Kernel_start(void)
{
    Kernel_task_start();
}

void Kernel_yield(void)
{
    Kernel_task_scheduler();
}
