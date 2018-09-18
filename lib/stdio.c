/*
 * stdio.c
 *
 *  Created on: Sep 17, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"


uint32_t putstr(const char* s)
{
    uint32_t c = 0;
    while(*s)
    {
        Hal_uart_put_char(*s++);
        c++;
    }
    return c;
}
