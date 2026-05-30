#ifndef __COMMON_DEBUG_H__
#define __COMMON_DEBUG_H__  

#include "stm32f10x.h"
#include"system_stm32f10x.h"
#include "Dri_usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void Common_Debug_Init(void);


#define DEBUG

#ifdef  DEBUG

#define FILE_NAME ( strrchr(__FILE__,'\\')? strrchr(__FILE__,'\\')+1: __FILE__)

#define debuge_printf(format, ...) printf("[%20s:%d]" format "\r\n", FILE_NAME, __LINE__, ##__VA_ARGS__)
#else
#define debuge_printf(format, ...)
#endif

#endif
