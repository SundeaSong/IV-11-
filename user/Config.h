#ifndef _CONFIG_H_	
#define _CONFIG_H_

#ifdef __cplusplus		   //定义对CPP进行C处理 //开始部分
extern "C" {
#endif

#include <math.h>
#include <string.h>			//字符串比较
#include <ctype.h>			//大写转换
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
	
#include "stm32f10x.h"		//STM32固件库
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
	
#include "bsp.h"			//板级初始化
#include "static_init.h"	//printf
#include "GPIO_Init.h"
#include "BKP_Init.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "hw_config.h"
#include "socket.h"
//#include "w5500.h"

//#include "SPI1_Init.h"
//#include "SPI2_Init.h"
//#include "spi_flash.h"
#include "I2CEEPROM.h"
#include "ADC.h"   

#include "HX711.H"

#include "USART1_init.h"
#include "USART2_init.h"
#include "USART3_init.h"
#include "USART4_init.h"
#include "USART5_init.h"

#include "usb_hid.h"
#include "Time2.h"
#include "DS3231.h"

#include "dht11.h"
#include "hv5812.h"
#include "ds18b20.h"


#define LED_LED1_OFF()   	GPIO_SetBits(GPIOA, GPIO_Pin_9 );  	   //LED1 
#define LED_LED1_ON()  		GPIO_ResetBits(GPIOA, GPIO_Pin_9 ); 
	//btn1		btn2		btn3		btn4
	//PA8		PB15		PB14		PB13
	//k2		k3			k4			k5
	//meun		set			down		up
#define key_Menu	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)		//菜单键
#define key_Set		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)		//选择键
#define key_Down	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)		//数字减
#define key_Up		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)		//数字加
//#define LED_LED2_OFF()   	GPIO_SetBits(GPIOC, GPIO_Pin_13 );  	   //LED2
//#define LED_LED2_ON()  		GPIO_ResetBits(GPIOC, GPIO_Pin_13 ); 
#define WAIT_TIME 		3

#define  SOCK_MONITOR	 0
#define  SOCK_COMMUN	 1	

extern	unsigned char shi1;
extern	unsigned char shi2;
extern	unsigned char fen1;
extern	unsigned char fen2;
extern	unsigned char miao1;
extern	unsigned char miao2;
	
extern	unsigned char nian1;
extern	unsigned char nian2;
extern	unsigned char yue1;
extern	unsigned char yue2;
extern	unsigned char ri1;
extern	unsigned char ri2;

extern  unsigned char t1,t2,t3,t4;

extern uint8 buffer[4096];/*定义一个2KB的缓存*/

extern const unsigned char Ascill_16[];
void DisplayTime(void);
void DisplayTemp(void);


#ifdef __cplusplus		   //定义对CPP进行C处理 //结束部分
}

#endif

#endif
