#include "Dri_Systick.h"
#include "Dri_Time5.h"
#include "Dri_Usart.h"

int main(void)
{

    Dri_Systick_Init();

    Com_Debug_Init();

    Dri_Tim5_Init();

    Dri_Tim5_SetDuty(0);

    int16_t duty = 100;
    int8_t step = 1; // 1: 变亮, 0: 变暗

    while (1)
    {

        // int8_t step = 1, duty = 100;
       

            if (duty >= 100 || duty <= 0)
            {
                step = -step;
            }
            duty += step;

            Dri_Tim5_SetDuty(duty);
             Dri_Systick_Delay_ms(50);
        

       
    }
}
