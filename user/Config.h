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

#include "SPI1_Init.h"
#include "SPI2_Init.h"
#include "spi_flash.h"
#include "I2CEEPROM.h"
#include "ADC.h"   

#include "HX711.H"

#include "USART1_init.h"
#include "USART2_init.h"
#include "USART3_init.h"
#include "USART4_init.h"
#include "USART5_init.h"

#include "usb_hid.h"


#define LED_LED1_OFF()   	GPIO_SetBits(GPIOA, GPIO_Pin_1 );  	   //LED1 
#define LED_LED1_ON()  		GPIO_ResetBits(GPIOA, GPIO_Pin_1 ); 	  

#define WAIT_TIME 		3

#define  SOCK_MONITOR	 0
#define  SOCK_COMMUN	 1	

extern uint8 buffer[4096];/*定义一个2KB的缓存*/

extern const unsigned char Ascill_16[];


#ifdef __cplusplus		   //定义对CPP进行C处理 //结束部分
}

#endif

#endif
