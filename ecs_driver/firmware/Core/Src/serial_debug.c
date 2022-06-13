#include "serial_debug.h"


void dbgprintf(char *debug_str, ...)
{
    va_list args;
    char byte = 0;
    char val;

    va_start(args, debug_str);

    while (*debug_str++) {
        if(*debug_str != '%')
        {
            byte = *debug_str;
        }
        else
        {
            switch (*++debug_str)
            {
                case 'd':
                    byte = va_arg(args, int);
                    break;
                case 'f':
                    byte = va_arg(args, double);
                    break;
                default:
                    break;
            }
        }

        HAL_UART_Transmit(&debug, (uint8_t*)&byte, 1, 10);
    }

    va_end(args);
}