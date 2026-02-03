#include "Dri_RTC.h"


void Dri_rtc_configuration(void)
{
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR| RCC_APB1Periph_BKP,ENABLE);//开启备份电源和备份接口的时钟

    // 默认情况下开启写保护，防止意外修改
    PWR_BackupAccessCmd(ENABLE);

    // 如果是第一次使用RTC，或者想要重新设置时间，就需要初始化RTC
    BKP_DeInit();

    RCC_LSEConfig(RCC_LSE_ON); // 打开外部低速晶振

    // 等待外部时钟稳定
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET)
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
    
    // 使能rtc中断，每隔一秒就会触发一次中断
    RTC_ITConfig(RTC_IT_SEC,ENABLE);//使能秒中断
    RTC_WaitForLastTask();

}
