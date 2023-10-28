/*
 * synch.c
 *
 *  Created on: Nov 8, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "stdbool.h"

#include "synch.h"

#define DEF_SEM_MAX 8

static int32_t sSemMax;
static int32_t sSem;

static KernelMutex_t sMutex;

void Kernel_sem_init(int32_t max)
{
    sSemMax = (max <= 0) ? DEF_SEM_MAX : max;
    sSemMax = (max >= DEF_SEM_MAX) ? DEF_SEM_MAX : max;

    sSem = sSemMax;
}

bool Kernel_sem_test(void)
{
    if (sSem <= 0)
    {
        return false;
    }

    sSem--;

    return true;
}

void Kernel_sem_release(void)
{
    sSem++;

    if (sSem >= sSemMax)
    {
        sSem = sSemMax;
    }
}

void Kernel_mutex_init(void)
{
    sMutex.owner = 0;
    sMutex.lock = false;
}

bool Kernel_mutex_lock(uint32_t owner)
{
    if (sMutex.lock)
    {
        return false;
    }

    sMutex.owner = owner;
    sMutex.lock = true;
    return true;
}

bool Kernel_mutex_unlock(uint32_t owner)
{
    if (owner == sMutex.owner)
    {
        sMutex.lock = false;
        return true;
    }
    return false;
}

