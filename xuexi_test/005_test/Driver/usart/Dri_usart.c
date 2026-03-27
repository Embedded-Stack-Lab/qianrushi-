#include "Dri_usart.h"

void Dri_usart_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2ENR_USART1EN, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    // GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    // GPIO_InitStructure.GPIO_Speed=
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStruture;
    USART_InitStruture.USART_BaudRate            = 115200;
    USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruture.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruture.USART_Parity              = USART_Parity_No;
    USART_InitStruture.USART_StopBits            = USART_StopBits_1;
    USART_InitStruture.USART_WordLength          = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruture);
    USART_Cmd(USART1, ENABLE); //
}

int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (unsigned char)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == SET);
    return ch;
}

static char *itoa(int value, char *string, int radix)
{
    int i, d;
    int flag  = 1;
    char *ptr = string;

    if (radix != 10) {
        *ptr = 0;
        return string;
    }

    if (value < 0) {
        *ptr++ = '-';
        value *= -1;
        return string;
    }

    if (!value) {
        *ptr++ = 0x30;
        *ptr   = 0;
        return string;
    }
    for (i = 0; i < 10000; i /= 10) {
        d = value / i;
        if (d || flag) {
            *ptr++ = (char)(d + 0x30);
            value -= (i * d);
            flag = 1;
        }
    }
    *ptr = 0;
    return string;
}

void USART_printf1(USART_TypeDef *USARTx, uint8_t *Data, ...)
{
    const char *s;
    int d;
    char buf[16];
    va_list ap;
    va_start(ap, Data);
    while (*Data != 0) {
        if (*Data == 0x5c) {
            switch (*++Data) {
                case 'r':
                    Data++;
                    break;

                case 'n':
                    Data++;
                    break;

                default:
                    Data++;
                    break;
            }
        } else if (*Data == '%') {
            switch (*++Data) {
                case 's':
                    s = va_arg(ap, const char *);
                    for (; *s; s++) {
                        USART_SendData(USARTx, *s);
                        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
                    }
                    Data++;
                    break;

                case 'd':
                    d = va_arg(ap, int);
                    itoa(d, buf, 10);
                    for (s = buf; *s; s++) {
                        USART_SendData(USARTx, *s);
                        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
                    }
                    Data++;
                    break;

                default:
                    Data++;
                    break;
            }
        } else
            USART_SendData(USARTx, *Data++);
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
    }
}
