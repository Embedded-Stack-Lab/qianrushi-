#include "Common_Deebug.h"

void Common_Debug_Init(void)
{
    Dri_USART_Init();
}

int fputc(int ch,FILE *f){
    Dri_USART_SendByte((uint8_t)ch);
  
    // USART_SendData(USART1,(uint8_t)ch); 

    // while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);

    return ch;
}    

