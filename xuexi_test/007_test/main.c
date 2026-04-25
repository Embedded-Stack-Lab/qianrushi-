#include "Com_Debug.h"
#include "Dri_Systick.h"
#include "Dri_Time.h"
#include "Dri_Usart.h"
#include "Inf_Key.h"
#include "Inf_Led.h"

extern uint8_t tim2_1s_flag;

int main()
{

    Dri_Systick_Init();

    // Dri_usart_Init();

    // Dri_Time_PWMInit();

    Com_Debug_Init();

    //  Dri_Time_PWMInit();

    // LED_Init();
    // Led_off(1);
    // Led_off(2);
    // Led_off(3);
    // int8_t i = 0;

    Driver_Tim5_Init();
    Driver_Tim5_Start();

    int8_t step = 1, duty = 100;

    // debuge_printfln("duty=%d",(int)Dri_TIM_GetDuty());
    // debuge_printfln("op---------------------%d",tim2_1s_flag);

    while (1)
    {

        if (duty >= 100 || duty <= 0)
        {
            step = -step;
        }

        duty += step;

        Driver_Tim5_SetDuty(duty);

        Dri_Systick_Delay_ms(20);
    }

    // Led_on(1);
    // Dri_Systick_Delay_ms(20000);
    // Led_off(1);
    // Dri_Systick_Delay_ms(20000);

    // for (i = 0; i < 100; i++)
    // {

    //     Dri_TIM_SetDuty(i);
    //     Dri_Systick_Delay_ms(50);
    //     // i++;
    //     // debuge_printfln("duty=%d", (int)Dri_TIM_GetDuty());
    // }

    // for (i = 100; i >= 0; i--)
    // {
    //     Dri_TIM_SetDuty(100 - i);
    //     Dri_Systick_Delay_ms(50);
    // }

    // if (tim2_1s_flag)
    // {

    //     // Led_on(1);
    //    tim2_1s_flag=0;
    // //    debuge_printfln();
    //     debuge_printfln("45654654---------------------");
    // }
}

