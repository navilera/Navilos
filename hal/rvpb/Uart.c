/*
 * Uart.c
 *
 *  Created on: Sep 8, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "Uart.h"
#include "HalUart.h"

extern volatile PL011_t* Uart;

void Hal_uart_init(void)
{
    // Enable UART
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1;
    Uart->uartcr.bits.RXE = 1;
    Uart->uartcr.bits.UARTEN = 1;
}

void Hal_uart_put_char(uint8_t ch)
{
    while(Uart->uartfr.bits.TXFF);
    Uart->uartdr.all = (ch & 0xFF);
}

uint8_t Hal_uart_get_char(void)
{
    uint32_t data;

    while(Uart->uartfr.bits.RXFE);

    data = Uart->uartdr.all;

    // Check for an error flag
    if (data & 0xFFFFFF00)
    {
        // Clear the error
        Uart->uartrsr.all = 0xFF;
        return 0;
    }


    return (uint8_t)(data & 0xFF);
}
