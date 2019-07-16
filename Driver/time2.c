/*-----------------------------------------------------
********IO口反转说明，配合Motor Control Board，********
***************PWM1引脚对应PE14************************
***************PWM2引脚对应PE13************************
-----------------------------------------------------*/
#include "Time2.h"

unsigned int temp = 0;				//temp = 1000,计时1S

void TIM2_Init(void)
{
		TIM2_NVIC_Configuration();
		TIM2_Configuration();
}
void TIM2_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
////TIM_TimeBaseStructure.Tim_Period里面装的就是周期
////TIM_TimeBaseStructure.TIM_Prescaler里面装的是预分频系数
////如果TIM_Period是999,Tim_Prescaler是71,那么记满的事件就是1000us,相对应的周期就是1000us,
////所以频率 = 1000000/1000 = 1000Hz

/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=10000;		 								/* 自动重装载寄存器周期的值(计数值) */
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    /* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);																		/* 开启时钟 */
//    TIM_OCInitTypedDef TIM2_PWM;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/    
}

//void TIM2_PWM_Config(void)
//{
//	TIM_OCInitTypeDef TIM2_PWM;
//	TIM2_PWM.TIM_OCMode = TIM_OCMode_PWM2;
//	
//	
//}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/






void TIM3_Init(void)
{
		TIM3_NVIC_Configuration();
		TIM3_Configuration();
}
void TIM3_NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
////TIM_TimeBaseStructure.Tim_Period里面装的就是周期
////TIM_TimeBaseStructure.TIM_Prescaler里面装的是预分频系数
////如果TIM_Period是999,Tim_Prescaler是71,那么记满的事件就是1000us,相对应的周期就是1000us,
////所以频率 = 1000000/1000 = 1000Hz

/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
void TIM3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    TIM_DeInit(TIM3);
    TIM_TimeBaseStructure.TIM_Period=10000;		 								/* 自动重装载寄存器周期的值(计数值) */
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    /* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//    TIM_Cmd(TIM2, ENABLE);																		/* 开启时钟 */
    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/    
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
