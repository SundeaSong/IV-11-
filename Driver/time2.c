/*-----------------------------------------------------
********IO�ڷ�ת˵�������Motor Control Board��********
***************PWM1���Ŷ�ӦPE14************************
***************PWM2���Ŷ�ӦPE13************************
-----------------------------------------------------*/
#include "Time2.h"

unsigned int temp = 0;				//temp = 1000,��ʱ1S

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
////TIM_TimeBaseStructure.Tim_Period����װ�ľ�������
////TIM_TimeBaseStructure.TIM_Prescaler����װ����Ԥ��Ƶϵ��
////���TIM_Period��999,Tim_Prescaler��71,��ô�������¼�����1000us,���Ӧ�����ھ���1000us,
////����Ƶ�� = 1000000/1000 = 1000Hz

/*TIM_Period--1000   TIM_Prescaler--71 -->�ж�����Ϊ1ms*/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=10000;		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    /* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);																		/* ����ʱ�� */
//    TIM_OCInitTypedDef TIM2_PWM;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*�ȹرյȴ�ʹ��*/    
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
////TIM_TimeBaseStructure.Tim_Period����װ�ľ�������
////TIM_TimeBaseStructure.TIM_Prescaler����װ����Ԥ��Ƶϵ��
////���TIM_Period��999,Tim_Prescaler��71,��ô�������¼�����1000us,���Ӧ�����ھ���1000us,
////����Ƶ�� = 1000000/1000 = 1000Hz

/*TIM_Period--1000   TIM_Prescaler--71 -->�ж�����Ϊ1ms*/
void TIM3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    TIM_DeInit(TIM3);
    TIM_TimeBaseStructure.TIM_Period=10000;		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    /* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//    TIM_Cmd(TIM2, ENABLE);																		/* ����ʱ�� */
    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*�ȹرյȴ�ʹ��*/    
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
