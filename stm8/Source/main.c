#include "iostm8s103F3.h"
#include "../Include/basefunc.h"
#include "../Include/uart.h"
#include "../Include/timer.h"
#include "../Include/ds18b20.h"
#include <stdio.h>

main()
{
    asm("sim");    //关总中断
    led_init();
    uart1_init();
    timer_init();
    asm("rim");    //开总中断
    printf("********* STM8S-Discovery DS18B20 Test *********\r\n");
    printf("Build: %s  %s\r\n", __DATE__, __TIME__);
    while (1)
    {
        //uart1_send(i++);
        led_negate();
        delay_ms(1000);
        printf("%.2f \r\n", DS18B20_ReadTemperature());
        //temp = ReadTemputer();
        //uart1_send(temp>>8);
        //uart1_send(temp);
    }
}