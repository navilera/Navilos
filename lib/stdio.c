/*
 * stdio.c
 *
 *  Created on: Sep 17, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"

#define PRINTF_BUF_LEN  1024

static char sPrintf_buf[PRINTF_BUF_LEN];   // 1KB

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

uint32_t debug_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsprintf(sPrintf_buf, format, args);
    va_end(args);

    return putstr(sPrintf_buf);
}

uint32_t vsprintf(char* buf, const char* format, va_list arg)
{
    uint32_t c = 0;

    char     ch;
    char*    str;
    uint32_t uint;
    uint32_t hex;

    for (uint32_t i = 0 ; format[i] ; i++)
    {
        if (format[i] == '%')
        {
            i++;
            switch(format[i])
            {
            case 'c':
                ch = (char)va_arg(arg, int32_t);
                buf[c++] = ch;
                break;
            case 's':
                str = (char*)va_arg(arg, char*);
                if (str == NULL)
                {
                    str = "(null)";
                }
                while(*str)
                {
                    buf[c++] = (*str++);
                }
                break;
            case 'u':
                uint = (uint32_t)va_arg(arg, uint32_t);
                c += utoa(&buf[c], uint, utoa_dec);
                break;
            case 'x':
                hex = (uint32_t)va_arg(arg, uint32_t);
                c += utoa(&buf[c], hex, utoa_hex);
                break;
            }
        }
        else
        {
            buf[c++] = format[i];
        }
    }

    if (c >= PRINTF_BUF_LEN)
    {
        buf[0] = '\0';
        return 0;
    }

    buf[c] = '\0';
    return c;
}

uint32_t utoa(char* buf, uint32_t val, utoa_t base)
{
    uint32_t c = 0;
    int32_t  idx = 0;
    char     tmp[11];   // It is big enough for store 32 bit int

    do {
        uint32_t t = val % (uint32_t)base;
        if (t >= 10)
        {
            t += 'A' - '0' - 10;
        }
        tmp[idx] = (t + '0');
        val /= base;
        idx++;
    } while(val);

    // reverse
    idx--;
    while (idx >= 0)
    {
        buf[c++] = tmp[idx];
        idx--;
    }

    return c;
}
