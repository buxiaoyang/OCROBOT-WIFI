#include "iostm8s103F3.h"
#include "../Include/basefunc.h"
#include "../Include/uart.h"
#include "../Include/timer.h"
#include "../Include/ds18b20.h"
#include <stdio.h>

void ledFlash(uchar num)
{
    while(num--)
    {
        led_negate(); 
        delay_ms(100);
    }
}

main()
{
    float temp;
    asm("sim");    //关总中断
    led_init();
    uart1_init();
    timer_init();
    asm("rim");    //开总中断
    timeCount = 3600;
    while (1)
    {
        led_negate();
        if(timeCount > 1000)
        {
            temp = DS18B20_ReadTemperature();
            timeCount = 0;
            ledFlash(10);
            temp = DS18B20_ReadTemperature();
            printf("AT+Reset\r\n");
            ledFlash(50);
            printf("AT+MODE=1\r\n");
            ledFlash(50);
            printf("AT+JoinAP=\"hpguest\",\"\"\r\n");
            ledFlash(50);
            printf("AT+NewSTA=\"TCP\",\"www.buxiaoyang.com\",80\r\n");
            ledFlash(50);
            printf("AT+UpDate=142\r\n");
            ledFlash(10);
            printf("GET /IOT/TemperatureInsert.php?user=buxiaoyang&title=nanjingOffice&value=");
            printf("%06.2f", temp);
            printf(" HTTP/1.1\r\n");
            printf("Host: www.buxiaoyang.com\r\n");
            printf("Connection: Keep-Alive\r\n\r\n");
            ledFlash(100);
            printf("AT+UpDate=142\r\n");
            ledFlash(10);
            printf("GET /IOT/TemperatureInsert.php?user=buxiaoyang&title=nanjingOffice&value=");
            printf("%06.2f", temp);
            printf(" HTTP/1.1\r\n");
            printf("Host: www.buxiaoyang.com\r\n");
            printf("Connection: Keep-Alive\r\n\r\n");
        }
        delay_ms(1000);
    }
}