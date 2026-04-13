#include "Dri_Usart.h"
#include "Dri_Systick.h"
#include "Inf_Led.h"
#include "Com_Debug.h"
#include "Inf_Key.h"

int main()
{

    Dri_Systick_Init();

    Dri_usart_Init();

    Com_Debug_Init();

    LED_Init();
    Led_off(1);
    Led_off(2);
    Led_off(3);

    debuge_printfln("op---------------------");
    while (1)
    {
        Led_on(1);
        Dri_Systick_Delay_ms(20000);
        Led_off(1);
        Dri_Systick_Delay_ms(20000);
    }
}
