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
    UART1_BRR1 = 0x0D;     //9600������
    UART1_CR2_TEN = 1;     //������
    UART1_CR2_REN = 1;     //�������
    //UART1_CR2_RIEN = 1;    //�����ж�ʹ��
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
    while(*dat != '\0')           //�ж��ַ����Ƿ������
    {
        uart1_send(*dat);        //���͵����ַ�
        dat++;                 //�ַ���ַ��1��ָ������һ���ַ�
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

