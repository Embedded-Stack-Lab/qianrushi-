#ifndef __COMMON_DEBUG_H__
#define __COMMON_DEBUG_H__

#include"Inf_uart.h"
#include"stdio.h"
#include"string.h"

void Common_debug_init(void);

#define  DEBUG

#ifdef DEBUG
    #define debug_printf(fmt, ...) printf("[DBG] " fmt, ##__VA_ARGS__)
#else
    #define debug_printf(fmt, ...) 
#endif


#endif /* __COMMON_DEBUG_H__ */
