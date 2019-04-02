/*
 * Interrupt.c
 *
 *  Created on: Sep 21, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "memio.h"
#include "HalInterrupt.h"
#include "armcpu.h"

static InterHdlr_fptr sHandlers[INTERRUPT_HANDLER_NUM];

static uint32_t GetInterruptNum(void);
static void ClearInterruptNum(uint32_t n);

void Hal_interrupt_init(void)
{
    enable_irq();
}

void Hal_interrupt_enable(uint32_t interrupt_num)
{

}

void Hal_interrupt_disable(uint32_t interrupt_num)
{

}

void Hal_interrupt_register_handler(InterHdlr_fptr handler, uint32_t interrupt_num)
{
    sHandlers[interrupt_num] = handler;
}

void Hal_interrupt_run_handler(void)
{
    uint32_t interrupt_num = GetInterruptNum();

    if (sHandlers[interrupt_num] != NULL)
    {
        sHandlers[interrupt_num]();
    }

    ClearInterruptNum(interrupt_num);
}

static uint32_t GetInterruptNum(void)
{
    return 0;
}

static void ClearInterruptNum(uint32_t n)
{
}
