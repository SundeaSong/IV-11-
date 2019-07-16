/**
  ******************************************************************************
  * @file    USART/Printf/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
//#include "usb_istr.h"
//extern const unsigned int LED_Point_Ctrl[21];
unsigned int buff_flag = 0;

unsigned char shi1  = 0;
unsigned char shi2  = 0;
unsigned char fen1  = 0;
unsigned char fen2  = 0;
unsigned char miao1 = 0;
unsigned char miao2 = 0;

unsigned char nian1 = 0;
unsigned char nian2 = 0;
unsigned char yue1  = 0;
unsigned char yue2  = 0;
unsigned char ri1   = 0;
unsigned char ri2   = 0;

unsigned char temperature_count = 0;	//温度延时读取累加变量
unsigned char t1, t2, t3, t4;			//温度4位值，百位，十位，小数点1位，小数点2位
 void TIM2_IRQHandler(void)
{
//	unsigned char j = 0;
	
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
		buff_flag++;
		if(buff_flag == 50)			//60Hz
		{
			buff_flag = 0;
			get_show_time();
			nian1 = calendar.w_year /10;
			nian2 = calendar.w_year %10;
			yue1 = calendar.w_month /10;
			yue2 = calendar.w_month %10;
			ri1 = calendar.w_date /10;
			ri2 = calendar.w_date %10;
			
			shi1 = calendar.hour /10;
			shi2 = calendar.hour %10;
			fen1 = calendar.min /10;
			fen2 = calendar.min %10;
			miao1 = calendar.sec /10;
			miao2 = calendar.sec %10;
//			printf("年月日：%d%d,%d%d,%d%d\t时分秒：%d%d,%d%d,%d%d\r\n",nian1,nian2,yue1,yue2,ri1,ri2,shi1,shi2,fen1,fen2,miao1,miao2);
//			printf("Time:%d%d%d\r\n",calendar.hour,calendar.min,calendar.sec);
//			for(j = 0; j < 8;  j++)
//			{
//				HC595SendData(num8[j + nian1*8],num[j+nian2*8],num[j+80],num[j+yue1*8],num[j+yue2*8],num[j+80],num[j+ri1*8],num[j+ri2*8],1);
//				//									1       				8         			- 				1							2					-							1									3		
//				ScanLine(j);
//			}
//			for(j = 8; j < 16; j++)
//			{
//				HC595SendData(num[j*2 + shi1*16],num[j*2+shi2*16],num[j*2+160],num[j*2+fen1*16],num[j*2+fen2*16],num[j*2+160],num[j*2+miao1*16],num[j*2+miao2*16],1);
//				ScanLine(j-8);
//			}
//			for(j = 0; j < 8; j++)
//			{
//				HC595SendData(num[j*2 + shi1*16],num[j*2+shi2*16],num[j*2+160],num[j*2+fen1*16],num[j*2+fen2*16],num[j*2+160],num[j*2+miao1*16],num[j*2+miao2*16],0);
//				ScanLine(j+8);
//			}
//			for(j = 0; j < 8; j++)
//			{
//				HC595SendData(num[j*2 + shi1*16],num[j*2+shi2*16],num[j*2+160],num[j*2+fen1*16],num[j*2+fen2*16],num[j*2+160],num[j*2+miao1*16],num[j*2+miao2*16],0);
//				ScanLine(j+8);
//			}
//				for(j = 0; j < 16; j++)
//				{
//					HC595SendData(num[j + shi1*16],num[j+shi2*16],num[j+160],num[j+fen1*16],num[j+fen2*16],num[j+160],num[j+miao1*16],num[j+miao2*16],0);
//					ScanLine(j);
//				}
//				for(j = 0;j < 16; j++)
//				{
//					HC595SendData(wenzi[j*2],wenzi[j*2+1],wenzi[j*2+32],wenzi[j*2+33],wenzi[j*2+64],wenzi[j*2+65],wenzi[j*2+96],wenzi[j*2+97],1);
//					ScanLine(j);
//				}

		}
	}		 	
}

 void TIM3_IRQHandler(void)
{
	int temp = 0.0;
	if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);
		temperature_count++;
		if(temperature_count >= 100)
		{
			temperature_count = 0;
			temp = DS18B20_Get_Temp()*100;			//获取的温度为float类型的数据，放大十倍转int类型
//			temp <<= 2;
			t1 = temp/1000;							//十位
			t2 = temp/100%10;						//个位
			t3 = temp/10%10;						//小数点1位
			t4 = temp%10;							//小数点2位
		}
			
	}		 	
}
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Printf
  * @{
  */ 
/*----------------------------------------------------------------------------
  Notes:
  The length of the receive and transmit buffers must be a power of 2.
  Each buffer has a next_in and a next_out index.
  If next_in = next_out, the buffer is empty.
  (next_in - next_out) % buffer_size = the number of characters in the buffer.
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void USART1_Puts(char *str)
{

}
/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    //10ms中断定时器
    Program_Cycle_Nums++;
	if(Program_Cycle_Nums==50)
	{
		LED_LED1_ON();
	}
	else if(Program_Cycle_Nums==100)		//1S
	{
		LED_LED1_OFF();
		Program_Cycle_Nums=0;			
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  * @brief  This function handles TIM1 interrupt request.
  * @param  None
  * @retval : None
  */
void TIM1_UP_IRQHandler(void)
{

}

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{


}
/**
  * @brief  This function handles External lines 15 to 10 interrupt request.
  * @param  None
  * @retval None
  */
//void EXTI15_10_IRQHandler(void)
//{

//}
/*******************************************************************************
* Function Name  : USB_HP_CAN1_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts requests
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void USB_HP_CAN1_TX_IRQHandler(void)
//{
//}

///*******************************************************************************
//* Function Name  : USB_LP_CAN1_RX0_IRQHandler
//* Description    : This function handles USB Low Priority or CAN RX0 interrupts
//*                  requests.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void USB_LP_CAN1_RX0_IRQHandler(void)
//{
//}
//void USB_LP_CAN1_RX0_IRQHandler(void)
//{
//	  USB_Istr();
//}

//void USBWakeUp_IRQHandler(void)
//{
//  EXTI_ClearITPendingBit(EXTI_Line18);
//}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
