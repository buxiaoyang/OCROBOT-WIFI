#include "iostm8s103F3.h"
#include "../Include/basefunc.h"
#include "../Include/uart.h"
#include "../Include/timer.h"
#include "../Include/ds18b20.h"

main()
{
    float temp;
    asm("sim");    //�����ж�
    led_init();
    uart1_init();
    timer_init();
    asm("rim");    //�����ж�
    while (1)
    {
        //uart1_send(i++);
        led_negate();
        delay_ms(1000);
        temp = DS18B20_ReadTemperature();
        //temp = ReadTemputer();
        //uart1_send(temp>>8);
        //uart1_send(temp);
    }
}