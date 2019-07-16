#ifndef _RADIO_H_
#define _RADIO_H_

#include "config.h"

#define SDA_H GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define SDA_L GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define SDA_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)
#define SCL_H GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define SCL_L GPIO_ResetBits(GPIOB,GPIO_Pin_8)


void Radio_Init(void);
void Radio_Read(void);
void Get_Frequency(void);
void Get_Pll(void);
void Search(unsigned char mode);
void Auto_Search(unsigned char mode);

void I2C_START(void);
void I2C_STOP(void);
unsigned char I2C_WAITACK(void);
void I2C_ACK(void);
void I2C_NOACK(void);
void I2C_SENDBYTE(unsigned char byte);
static unsigned char I2C_RECEIVE_BYTE(void);
void ATIICxx_PWrite(unsigned char *McuAddress,unsigned char count);
void ATIICxx_PRead(unsigned char *McuAddress,unsigned char count);






#endif











