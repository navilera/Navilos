/*
 * Regs.c
 *
 *  Created on: Sep 8, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "Uart.h"

volatile PL011_t* Uart = (PL011_t*)UART_BASE_ADDRESS0;
