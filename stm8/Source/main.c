#include "iostm8s103F3.h"
#include "../Include/basefunc.h"
#include "../Include/uart.h"
#include "../Include/timer.h"
main()
{
    uchar i;
    asm("sim");    //�����ж�
    led_init();
    uart1_init();
    timer_init();
    asm("rim");    //�����ж�
    while (1)
    {
        uart1_send(i++);
    }
}