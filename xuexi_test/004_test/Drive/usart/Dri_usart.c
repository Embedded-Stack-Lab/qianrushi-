#include "Dri_usart.h"

void Dri_usart_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_Initstructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 未被正确初始化。代码中设置了GPIOA的时钟，但没有初始化GPIOA的模式和速度。

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_Initstructure.USART_BaudRate = 115200;
    USART_Initstructure.USART_WordLength = USART_WordLength_8b;
    USART_Initstructure.USART_StopBits = USART_StopBits_1;
    USART_Initstructure.USART_Parity = USART_Parity_No;
    USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Initstructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Cmd(USART1, ENABLE); // 未使能串口1，导致无法进行串口数据的传输
    USART_Init(USART1, &USART_Initstructure);
}

int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (unsigned char)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
        ;

    return ch;
}

static char *itoa(int value, char *string, int radix)
{

    int i, d;
    int flag = 0;
    char *ptr = string;
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }
    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }
    if (value < 0)
    {
        *ptr++ = '-';
        value *= -1;
    }
    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }
    *ptr = 0;
    return string;
}

void USART1_printf(USART_TypeDef *USARTx, uint8_t *Data, ...)
{
    const char *s;
    int d;
    char buf[16];
    va_list ap;
    va_start(ap, Data);
    while (*Data != 0)
    {
        if (*Data == 0x5c)
        {
            switch (*++Data)
            {
            case 'r':
                USART_SendData(USARTx, 0x0d);
                Data++;
                break;

            case 'n':
                USART_SendData(USARTx, 0x0a); // 换行0x0A是ascll的换行符
                Data++;
                break;

            default:
                Data++;
                break;
            }
        }
        else if (*Data == '%')
        {
            switch (*++Data)
            {
            case 's':
                s = va_arg(ap, const char *);
                for (; *s; s++)
                {
                    USART_SendData(USARTx, *s);
                    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
                        ;
                }
                Data++;
                break;

            case 'd':
                d = va_arg(ap, int);
                itoa(d, buf, 10);
                for (s = buf; *s; s++)
                {
                    USART_SendData(USART1, *s); // 把每个字符真正发出去
                    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
                        ;
                }
                Data++;
                break;

            default:
                Data++;
                break;
            }
        }
        else
            USART_SendData(USARTx, *Data++);
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
            ;
    }
}
