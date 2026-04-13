#ifndef __COMMONINT_H__
#define __COMMONINT_H__

#include"stm32f10x.h"
#include"Dri_Usart.h"
#include"string.h"

void Com_Debug_Init(void);

#define DEBUG
#ifdef DEBUG
#define FILE_NAME strrchr(__FILE__,'\\')?strrchr(__FILE__,'\\')+1:__FILE__

#define debuge_printfln(format,...)printf("[%20s:%d]" format "\r\n",FILE_NAME,__LINE__,##__VA_ARGS__)
#else
#define debug_printf(format,...)
#endif


#endif
