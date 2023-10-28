/*
 * Kernel.c
 *
 *  Created on: Oct 28, 2018
 *      Author: maanu
 */


#include "stdint.h"
#include "stdbool.h"

#include "armcpu.h"
#include "memio.h"
#include "Kernel.h"

void Kernel_start(void)
{
	enable_irq();
    Kernel_task_start();
}

void Kernel_yield(void)
{
    Kernel_task_scheduler();
}

void Kernel_send_events(uint32_t event_list)
{
    KernelEventFlag_t sending_event = KernelEventFlag_Empty;

    for (uint32_t i = 0 ; i < 32 ; i++)
    {
        if ((event_list >> i) & 1)
        {
            SET_BIT(sending_event, i);
            Kernel_event_flag_set(sending_event);
        }
    }
}

KernelEventFlag_t Kernel_wait_events(uint32_t waiting_list)
{
    KernelEventFlag_t waiting_event = KernelEventFlag_Empty;

    for (uint32_t i = 0 ; i < 32 ; i++)
    {
        if ((waiting_list >> i) & 1)
        {
            SET_BIT(waiting_event, i);

            if (Kernel_event_flag_check(waiting_event))
            {
                return waiting_event;
            }
        }
    }

    return KernelEventFlag_Empty;
}

bool Kernel_send_msg(KernelMsgQ_t Qname, void* data, uint32_t count)
{
    uint8_t* d = (uint8_t*)data;

	if (count > (MSG_Q_SIZE_BYTE - Kernel_msgQ_count(Qname)))
	{
		return false;
	}

    for (uint32_t i = 0 ; i < count ; i++)
    {
        if (false == Kernel_msgQ_enqueue(Qname, *d))
        {
            return false;
        }
        d++;
    }

    return true;
}

uint32_t Kernel_recv_msg(KernelMsgQ_t Qname, void* out_data, uint32_t count)
{
    uint8_t* d = (uint8_t*)out_data;

    for (uint32_t i = 0 ; i < count ; i++)
    {
        if (false == Kernel_msgQ_dequeue(Qname, d))
        {
            return i;
        }
        d++;
    }

    return count;
}

void Kernel_flush_msg(KernelMsgQ_t Qname)
{
	uint8_t d = 0;

	while(true)
	{
		if (false == Kernel_msgQ_dequeue(Qname, &d))
		{
			break;
		}
	}
}

void Kernel_lock_sem(void)
{
    while(false == Kernel_sem_test())
    {
        Kernel_yield();
    }
}

void Kernel_unlock_sem(void)
{
    Kernel_sem_release();
}

void Kernel_lock_mutex(void)
{
    while(true)
    {
        uint32_t current_task_id = Kernel_task_get_current_task_id();
        if (false == Kernel_mutex_lock(current_task_id))
        {
            Kernel_yield();
        }
        else
        {
            break;
        }
    }
}

void Kernel_unlock_mutex(void)
{
    uint32_t current_task_id = Kernel_task_get_current_task_id();
    if (false == Kernel_mutex_unlock(current_task_id))
    {
        Kernel_yield();
    }
}
