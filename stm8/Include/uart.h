#ifndef __UART_H__
#define __UART_H__
#include "parameters.h"

void  uart1_init(void);
void  uart1_send(uchar dat);
int putchar(int c);
//void uart1_sendString(uchar *dat);

extern uchar receiveBuf[100];
extern uchar receiveIndex;
#endif