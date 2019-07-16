#ifndef _HV5812_H_
#define _HV5812_H_

#include "config.h"

//HV5812		DIn:PA7			Clock:PB0
//				Load:PA5		Blank:PA6
#define Din_ON			GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define Din_OFF			GPIO_ResetBits(GPIOA, GPIO_Pin_7)

#define Load_ON			GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define Load_OFF		GPIO_ResetBits(GPIOA, GPIO_Pin_5)

#define Clock_ON		GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define Clock_OFF		GPIO_ResetBits(GPIOB, GPIO_Pin_0)

#define Blank_ON		GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define Blank_OFF		GPIO_ResetBits(GPIOA, GPIO_Pin_6)

void HV5812_Config(void);
void hv5812_init(void);
void hv5812_data(unsigned int data,unsigned char num);







#endif


