/*
 * event.h
 *
 *  Created on: Nov 2, 2018
 *      Author: maanu
 */

#ifndef KERNEL_EVENT_H_
#define KERNEL_EVENT_H_

typedef enum KernelEventFlag_t
{
    KernelEventFlag_UartIn      = 0x00000001,
    KernelEventFlag_CmdIn       = 0x00000002,
    KernelEventFlag_CmdOut      = 0x00000004,
    KernelEventFlag_Unlock      = 0x00000008,
    KernelEventFlag_Reserved04  = 0x00000010,
    KernelEventFlag_Reserved05  = 0x00000020,
    KernelEventFlag_Reserved06  = 0x00000040,
    KernelEventFlag_Reserved07  = 0x00000080,
    KernelEventFlag_Reserved08  = 0x00000100,
    KernelEventFlag_Reserved09  = 0x00000200,
    KernelEventFlag_Reserved10  = 0x00000400,
    KernelEventFlag_Reserved11  = 0x00000800,
    KernelEventFlag_Reserved12  = 0x00001000,
    KernelEventFlag_Reserved13  = 0x00002000,
    KernelEventFlag_Reserved14  = 0x00004000,
    KernelEventFlag_Reserved15  = 0x00008000,
    KernelEventFlag_Reserved16  = 0x00010000,
    KernelEventFlag_Reserved17  = 0x00020000,
    KernelEventFlag_Reserved18  = 0x00040000,
    KernelEventFlag_Reserved19  = 0x00080000,
    KernelEventFlag_Reserved20  = 0x00100000,
    KernelEventFlag_Reserved21  = 0x00200000,
    KernelEventFlag_Reserved22  = 0x00400000,
    KernelEventFlag_Reserved23  = 0x00800000,
    KernelEventFlag_Reserved24  = 0x01000000,
    KernelEventFlag_Reserved25  = 0x02000000,
    KernelEventFlag_Reserved26  = 0x04000000,
    KernelEventFlag_Reserved27  = 0x08000000,
    KernelEventFlag_Reserved28  = 0x10000000,
    KernelEventFlag_Reserved29  = 0x20000000,
    KernelEventFlag_Reserved30  = 0x40000000,
    KernelEventFlag_Reserved31  = 0x80000000,

    KernelEventFlag_Empty       = 0x00000000,
} KernelEventFlag_t;

void Kernel_event_flag_init(void);
void Kernel_event_flag_set(KernelEventFlag_t event);
void Kernel_event_flag_clear(KernelEventFlag_t event);
bool Kernel_event_flag_check(KernelEventFlag_t event);

#endif /* KERNEL_EVENT_H_ */
