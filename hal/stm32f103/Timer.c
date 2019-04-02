/*
 * Timer.c
 *
 *  Created on: Sep 27, 2018
 *      Author: yiman
 */

#include "stdint.h"
#include "stdio.h"

#include "HalTimer.h"


static uint32_t sInternal_1ms_counter;

void Hal_timer_init(void)
{
}

uint32_t Hal_timer_get_1ms_counter(void)
{
    return sInternal_1ms_counter;
}

