#include "iostm8s103F3.h"
#include "../Include/basefunc.h"

void  delay_ms(uint  ms)
{
    uchar  i,j;
    while(ms--)
    {
        for(i=4;i!=0;i--)
          for(j=100;j!=0;j--);
    }
}

void led_init(void)
{
    PB_DDR |= (1<<5);
    PB_CR1 |= (1<<5);
    PB_CR2 |= (1<<5);
    PB_ODR |= (1<<5);
}

void led_status(uchar out)
{
    if(out)
    {
        PB_ODR |= (1<<5);
    }
    else
    {
        PB_ODR &= ~(1<<5);
    }
}

void led_negate(void)
{
    if(PB_ODR &= (1<<5))
    {
        PB_ODR &= ~(1<<5);
    }
    else
    {
        PB_ODR |= (1<<5);
    }
}

