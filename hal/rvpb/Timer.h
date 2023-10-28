/*
 * Timer.h
 *
 *  Created on: Sep 27, 2018
 *      Author: yiman
 */

#ifndef HAL_RVPB_TIMER_H_
#define HAL_RVPB_TIMER_H_

typedef union TimerXControl_t
{
    uint32_t all;
    struct {
        uint32_t OneShot:1;     //0
        uint32_t TimerSize:1;   //1
        uint32_t TimerPre:2;    //3:2
        uint32_t Reserved0:1;   //4
        uint32_t IntEnable:1;   //5
        uint32_t TimerMode:1;   //6
        uint32_t TimerEn:1;     //7
        uint32_t Reserved1:24;  //31:8
    } bits;
} TimerXControl_t;

typedef union TimerXRIS_t
{
    uint32_t all;
    struct {
        uint32_t TimerXRIS:1;   //0
        uint32_t Reserved:31;   //31:1
    } bits;
} TimerXRIS_t;

typedef union TimerXMIS_t
{
    uint32_t all;
    struct {
        uint32_t TimerXMIS:1;   //0
        uint32_t Reserved:31;   //31:1
    } bits;
} TimerXMIS_t;

typedef struct Timer_t
{
    uint32_t        timerxload;     // 0x00
    uint32_t        timerxvalue;    // 0x04
    TimerXControl_t timerxcontrol;  // 0x08
    uint32_t        timerxintclr;   // 0x0C
    TimerXRIS_t     timerxris;      // 0x10
    TimerXMIS_t     timerxmis;      // 0x14
    uint32_t        timerxbgload;   // 0x18
} Timer_t;

#define TIMER_CPU_BASE  0x10011000
#define TIMER_INTERRUPT 36

#define TIMER_FREERUNNING   0
#define TIMER_PERIOIC       1

#define TIMER_16BIT_COUNTER 0
#define TIMER_32BIT_COUNTER 1

#define TIMER_1MZ_INTERVAL       (1024 * 1024)

#endif /* HAL_RVPB_TIMER_H_ */
