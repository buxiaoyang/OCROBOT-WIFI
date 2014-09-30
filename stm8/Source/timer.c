#include "iostm8s103F3.h"
#include "../Include/timer.h"
#include "../Include/basefunc.h"

uint timer1s = 0;

void  timer_init(void)
{
    TIM1_PSCRH = 0;
    TIM1_PSCRL = 1;          //(1+1)��ƵΪ1M
    TIM1_ARRH = 0x3;
    TIM1_ARRL = 0xE8;        //ÿ1000us�ж�һ��
    TIM1_IER = 0x01;         //��������ж�
    TIM1_CR1 = 0x01;         //������ʹ�ܣ���ʼ����
}

#pragma   vector = TIM1_OVR_UIF_vector
__interrupt void TIM1_OVR_UIF(void)
{
    TIM1_SR1_UIF = 0;
    //add your code here
    timer1s ++;
    if(timer1s > 1000)
    {
        //led_negate();
        timer1s = 0;
    }
}

