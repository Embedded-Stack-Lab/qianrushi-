#include "common_debug.h"

void Common_debug_init(void)
{
    Inf_uart_config();
}

int fputc(int c,FILE *f){

    Inf_uart_sendchar(USART1,(uint8_t)c);
    return c;

}
