#include "Inf/Inf_led.h"

int main()
{

    LED_Init();
    Delay_Init();

    while (1) {
        for (int i = 1; i < 4; i++) {

            Led_on(i);
            Delay_s(1);
            Led_off(i);
        }
    }
}
