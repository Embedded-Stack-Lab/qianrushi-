#include "Dri_RTC.h"

int TimeDisplay = 0;
void Dri_rtc_configuration(void)
{

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); // 开启备份电源和备份接口的时钟

    // 默认情况下开启写保护，防止意外修改
    PWR_BackupAccessCmd(ENABLE);

    // 如果是第一次使用RTC，或者想要重新设置时间，就需要初始化RTC
    BKP_DeInit();

    RCC_LSEConfig(RCC_LSE_ON); // 打开外部低速晶振

    // 等待外部时钟稳定
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {
        // 预留写入超时函数
    }

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // 设置RTC时钟源为外部低速晶振

    RCC_RTCCLKCmd(ENABLE); // 使能RTC时钟

    // 等待外部的寄存器同步
    RTC_WaitForLastTask();

    // 等待上次操作的完成
    RTC_WaitForLastTask();

    // 设置RTC预分频值
    RTC_SetPrescaler(32767); // 1秒钟计数一次
    RTC_WaitForLastTask();

    // 设置RTC初始时间为 00:00:00（共0秒）
    // 如果需要设置其他时间，比如 12:30:45，则应设置为：12*3600 + 30*60 + 45 = 45045
    RTC_SetCounter(0);
    RTC_WaitForLastTask();

    // 使能rtc中断，每隔一秒就会触发一次中断
    RTC_ITConfig(RTC_IT_SEC, ENABLE); // 使能秒中断
    RTC_WaitForLastTask();
}

static void Time_Display(uint32_t TimeVar)
{
    uint32_t THH = 0, TMM = 0, TSS = 0;

    /* 1. 把总秒数算成小时 (1小时 = 3600秒) */
    THH = TimeVar / 3600;

    /* 2. 把剩下的秒数算成分钟 (1分钟 = 60秒) */
    TMM = (TimeVar % 3600) / 60;

    /* 3. 剩下的就是秒 */
    TSS = (TimeVar % 3600) % 60;

    /* 4. 打印出来 (比如 12:05:30) */
    printf("Time: %0.2d:%0.2d:%0.2d\r\n", THH, TMM, TSS);
}

void Dri_rtc_TimeShow(void)
{
    USART1_printf(USART1, "\r\n");

    while (1)
    {
        if (TimeDisplay == 1)
        {
            Time_Display(RTC_GetCounter());
            TimeDisplay = 0;
        }
    }
}

void NVIC_Configuration(void)
{

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);           // 设置优先级分组2
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;            // RTC中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 抢占优先级1，子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 使能中断
    NVIC_Init(&NVIC_InitStructure);                           // 初始化NVIC
}
