/******** STM8S-Discovery DS18B20 Test ********
* �汾.........: 1.0
* ����.........: ������
* Ŀ��.........: STM8S105C6T6
* �ļ���.......: main.c
* ��������.....: IAR for STM8 V1.1
* ����ʱ��.....: 2010.09.10
* ����޸�.....: 2010.09.10
***********************************************/

#include "iostm8s103F3.h"
#include "../Include/ds18b20.h"
#include "../Include/basefunc.h"

#define DS18B20_DQ_OUT          PC_DDR |= (1<<3)    //���
#define DS18B20_DQ_IN           PC_DDR &= ~(1<<3)   //����
#define DS18B20_DQ_HIGH         PC_ODR |= (1<<3)    //����
#define DS18B20_DQ_LOW          PC_ODR &= ~(1<<3)   //����
#define DS18B20_DQ_PULL_UP      PC_CR1 |= (1<<3)    //����
#define DS18B20_DQ_FLOATING     PC_CR1 &= ~(1<<3)     //����
#define DS18B20_DQ_PUSH_PULL    PC_CR1 |= (1<<3)     //����
#define DS18B20_DQ_OPEN_DRAIN   PC_CR1 &= ~(1<<3)     //��©
#define DS18B20_DQ_VALUE        PC_IDR & (1<<3)        //DQֵ


void DS18B20_Init(void)
{
    DS18B20_DQ_OUT;   
    DS18B20_DQ_PUSH_PULL;    
    DS18B20_DQ_HIGH;   
    delay_10us(1);
    DS18B20_DQ_LOW;   
    delay_10us(60);     //��λ����
    
    DS18B20_DQ_IN;   
    DS18B20_DQ_PULL_UP;    
    delay_10us(10);     
    while(DS18B20_DQ_VALUE);
    delay_10us(40);
}

void DS18B20_WriteByte(uchar _data)
{
    uchar i = 0;

    DS18B20_DQ_OUT;
    for (i = 0; i < 8; i++)
    {
        DS18B20_DQ_LOW;
        delay_10us(1);
        if (_data & 0x01)
        {
            DS18B20_DQ_HIGH;
        }
        _data >>= 1;
        delay_10us(6);
        DS18B20_DQ_HIGH;
    }
}

uchar DS18B20_ReadByte(void)
{
    uchar i = 0, _data = 0;

    for (i = 0; i < 8; i++)
    {
        DS18B20_DQ_OUT;
        DS18B20_DQ_LOW;
        delay_10us(1);
        _data >>= 1;
        DS18B20_DQ_HIGH;
        DS18B20_DQ_IN;
        if (DS18B20_DQ_VALUE)
        {
            _data |= 0x80;
        }
        DS18B20_DQ_OUT; 
        DS18B20_DQ_HIGH;
        delay_10us(6);
    }

    return _data;
}

float DS18B20_ReadTemperature(void)
{
    uchar temp = 0;
    float t = 0;
    
    DS18B20_Init();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0x44);

    DS18B20_Init();
    DS18B20_WriteByte(0xcc);
    DS18B20_WriteByte(0xbe);

    temp = DS18B20_ReadByte();
    t = (((temp & 0xf0) >> 4) + (temp & 0x07) * 0.125); 
    temp = DS18B20_ReadByte();
    t += ((temp & 0x0f) << 4);
    return t;
}


