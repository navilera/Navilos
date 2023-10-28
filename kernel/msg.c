/*
 * msg.c
 *
 *  Created on: Nov 6, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

#include "msg.h"

static KernelCirQ_t sMsgQ[KernelMsgQ_Num];

void Kernel_msgQ_init(void)
{
    for (uint32_t i = 0 ; i < KernelMsgQ_Num ; i++)
    {
        sMsgQ[i].front = 0;
        sMsgQ[i].rear = 0;
        memclr(sMsgQ[i].Queue, MSG_Q_SIZE_BYTE);
    }
}

bool Kernel_msgQ_is_empty(KernelMsgQ_t Qname)
{
    if (Qname >= KernelMsgQ_Num)
    {
        return false;
    }

    if (sMsgQ[Qname].front == sMsgQ[Qname].rear)
    {
        return true;
    }

    return false;
}

bool Kernel_msgQ_is_full(KernelMsgQ_t Qname)
{
    if (Qname >= KernelMsgQ_Num)
    {
        return false;
    }

    if (((sMsgQ[Qname].rear + 1) % MSG_Q_SIZE_BYTE) == sMsgQ[Qname].front)
    {
        return true;
    }

    return false;
}

bool Kernel_msgQ_enqueue(KernelMsgQ_t Qname, uint8_t data)
{
    if (Qname >= KernelMsgQ_Num)
    {
        return false;
    }

    if (Kernel_msgQ_is_full(Qname))
    {
        return false;
    }
    sMsgQ[Qname].rear++;
    sMsgQ[Qname].rear %= MSG_Q_SIZE_BYTE;

    uint32_t idx = sMsgQ[Qname].rear;
    sMsgQ[Qname].Queue[idx] = data;

    return true;
}

bool Kernel_msgQ_dequeue(KernelMsgQ_t Qname, uint8_t* out_data)
{
    if (Qname >= KernelMsgQ_Num)
    {
        return false;
    }

    if (Kernel_msgQ_is_empty(Qname))
    {
        return false;
    }

    sMsgQ[Qname].front++;
    sMsgQ[Qname].front %= MSG_Q_SIZE_BYTE;

    uint32_t idx = sMsgQ[Qname].front;
    *out_data = sMsgQ[Qname].Queue[idx];

    sMsgQ[Qname].Queue[idx] = 0;	// clear

    return true;
}

uint32_t Kernel_msgQ_count(KernelMsgQ_t Qname)
{
	return sMsgQ[Qname].rear - sMsgQ[Qname].front;
}
