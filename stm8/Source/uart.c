#include "iostm8s103F3.h"
#include "../Include/uart.h"

uchar receiveBuf[100] = {0};
uchar receiveIndex = 0;

void  uart1_init(void)
{
    UART1_CR1=0x00;
    UART1_CR2=0x00;
    UART1_CR3=0x00;
    UART1_BRR2 = 0x00;
    UART1_BRR1 = 0x0D;     //9600波特率
    UART1_CR2_TEN = 1;     //允许发送
    UART1_CR2_REN = 1;     //允许接收
    //UART1_CR2_RIEN = 1;    //接收中断使能
}

void  uart1_send(uchar dat)
{
    while((UART1_SR & 0x80)==0x00);
    UART1_DR = dat;
}

int putchar(int c)
{
    uart1_send(c);
    return c;
}

/*
void uart1_sendString(uchar *dat)
{
    while(*dat != '\0')           //判断字符串是否发送完毕
    {
        uart1_send(*dat);        //发送单个字符
        dat++;                 //字符地址加1，指向先下一个字符
    }
}
*/


#pragma   vector = UART1_R_RXNE_vector
__interrupt void uart1rxd(void)
{
    //data = UART1_DR;
    if(receiveIndex == 100)
    {
        receiveIndex = 0;
    }
    receiveBuf[receiveIndex++] = UART1_DR;
}

