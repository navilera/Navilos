/*
 * Regs.c
 *
 *  Created on: Sep 8, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "Uart.h"
#include "Interrupt.h"
#include "Timer.h"

volatile PL011_t*   Uart    = (PL011_t*)UART_BASE_ADDRESS0;
volatile GicCput_t* GicCpu  = (GicCput_t*)GIC_CPU_BASE;
volatile GicDist_t* GicDist = (GicDist_t*)GIC_DIST_BASE;
volatile Timer_t*   Timer   = (Timer_t*)TIMER_CPU_BASE;
