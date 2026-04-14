#include "Dri_Usart.h"
#include "Dri_Systick.h"
#include "Inf_Led.h"
#include "Com_Debug.h"
#include "Inf_Key.h"

extern uint8_t tim2_1s_flag;

int main()
{

    Dri_Systick_Init();

    Dri_usart_Init();

    Com_Debug_Init();

    LED_Init();
    Led_off(1);
    Led_off(2);
    Led_off(3);

    // debuge_printfln("op---------------------%d",tim2_1s_flag);
    while (1)
    {
        // Led_on(1);
        // Dri_Systick_Delay_ms(20000);
        // Led_off(1);
        // Dri_Systick_Delay_ms(20000);

        if (tim2_1s_flag)
        {
            Led_on(1);
           tim2_1s_flag=0;
             debuge_printfln("45654654---------------------");
        }
        

    }
}
