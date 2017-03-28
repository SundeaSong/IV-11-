#ifndef _USART1_INIT_H_	
#define _USART1_INIT_H_

#ifdef __cplusplus									  //定义对CPP进行C处理
extern "C" {
#endif

#include "Config.h"

#define USART1BaudRate		38400		   			  													//定义串口1的波特率


void USART1_Config(void);		  								//串口配置
void USART1_RX_Buffer_Clear(void); 						//清空接收缓冲区

void USART1_SendByte(u8 Data);								//单字符数据发送
void USART1_SendString(u8* Data,u32 Len);			//多字符发送
void USART1_DMASendString(char* Data,u32 Len);	//DMA多字符发送

#ifdef __cplusplus		   //定义对CPP进行C处理 //结束部分
}
#endif

#endif
