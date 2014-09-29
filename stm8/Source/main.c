#include "iostm8s103F3.h"
#include "../Include/basefunc.h"
#include "../Include/uart.h"
#include "../Include/timer.h"
main()
{
    uchar i;
    asm("sim");    //关总中断
    led_init();
    uart1_init();
    timer_init();
    asm("rim");    //开总中断
    while (1)
    {
        uart1_send(i++);
    }
}