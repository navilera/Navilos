/*
 * armcpu.c
 *
 *  Created on: Sep 22, 2018
 *      Author: maanu
 */

#include "armcpu.h"

void enable_irq(void)
{
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS  r0, cpsr");
    __asm__ ("BIC  r1, r0, #0x80");
    __asm__ ("MSR  cpsr, r1");
    __asm__ ("POP {r0, r1}");
}

void enable_fiq(void)
{
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS  r0, cpsr");
    __asm__ ("BIC  r1, r0, #0x40");
    __asm__ ("MSR  cpsr, r1");
    __asm__ ("POP {r0, r1}");
}

void disable_irq(void)
{
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS  r0, cpsr");
    __asm__ ("ORR  r1, r0, #0x80");
    __asm__ ("MSR  cpsr, r1");
    __asm__ ("POP {r0, r1}");
}

void disable_fiq(void)
{
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS  r0, cpsr");
    __asm__ ("ORR  r1, r0, #0x40");
    __asm__ ("MSR  cpsr, r1");
    __asm__ ("POP {r0, r1}");
}
