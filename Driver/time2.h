#ifndef TIME2_H
#define TIME2_H

#include "config.h"
 
#define START_TIME  time=0;RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);TIM_Cmd(TIM2, ENABLE)
#define STOP_TIME  TIM_Cmd(TIM2, DISABLE);RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE)

void TIM2_Init(void);
void TIM2_NVIC_Configuration(void);
void TIM2_Configuration(void);

void TIM3_Init(void);
void TIM3_NVIC_Configuration(void);
void TIM3_Configuration(void);


#endif	/* TIME_TEST_H */
