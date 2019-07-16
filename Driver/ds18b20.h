#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "config.h"

#define HIGH  1 
#define LOW   0

#define DS18B20_CLK     RCC_APB2Periph_GPIOB
#define DS18B20_PIN      GPIO_Pin_12                  
#define DS18B20_PORT GPIOB                  //总体代表DS18B20的GPIO口为PB112

//带参宏，可以像内联函数一样使用,输出高电平或低电平
#define DS18B20_DATA_OUT(a)if (a) \
GPIO_SetBits(GPIOB,GPIO_Pin_12);\
else \
GPIO_ResetBits(GPIOB,GPIO_Pin_12)
 //读取引脚的电平
#define  DS18B20_DATA_IN()  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)

uint8_t DS18B20_Init(void);
//float DS18B20_Get_Temp(uint8_t *a,uint8_t b);
void read_serial(uint8_t *serial);
float DS18B20_Get_Temp(void);


#endif
