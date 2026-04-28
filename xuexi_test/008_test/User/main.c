#include "Dri_Systick.h"
#include "Dri_Time5.h"
#include "Dri_Usart.h"
#include "Com_Debug.h"
#include "Dri_key.h"

int main(void)
{

    Dri_Systick_Init();

    Com_Debug_Init();

    Dri_Tim5_Init();

    Dri_Tim5_Start();

		Dri_Key_Init();
	
    Dri_Tim5_SetDuty(0);

    int16_t duty = 100;
    int8_t step = 0; // 1: 变亮, 0: 变暗

    while (1)
    {


        uint8_t key_state=Dri_Key_Scan();
			

        if (!key_state)
        {
					Dri_Systick_Delay_ms(20);
            if (key_state == KEY_ONE&&step>=0)
            {
							debuge_printfln("1");
                duty=step+10;
						
            }
            else if (key_state == KEY_TWO&&step>=0){
                duty=step-10;
            }else if (key_state == KEY_THREE&&step<=0){
                duty=100;
            }
							Dri_Tim5_SetDuty(duty);
        }
        

    //     int8_t step = 1, duty = 100;
       


    //         if (duty >= 100 || duty <= 0)
    //         {
    //             step = -step;
    //         }
    //         duty += step;

    //          Dri_Tim5_SetDuty(duty);
    //          Dri_Systick_Delay_ms(1);
    //         //  debuge_printfln("10%"); 
             
    //         //  Dri_Tim5_SetDuty(50);
    //         //  Dri_Systick_Delay_ms(5000);
    //         //  debuge_printfln("50%"); 

             
    //         //  Dri_Tim5_SetDuty(100);
    //         //  Dri_Systick_Delay_ms(5000);
    //         //  debuge_printfln("100%"); 
        

       
    }
}
