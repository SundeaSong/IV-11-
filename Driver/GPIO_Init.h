#ifndef _GPIO_INIT_H_	
#define _GPIO_INIT_H_

#ifdef __cplusplus			//定义对CPP进行C处理
extern "C" {
#endif

#include "Config.h"

#define ON  0
#define OFF 1

#define SW_ID_0       GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9)
#define SW_ID_1       GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)
#define SW_ID_2       GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)	
	
#define X1			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define X2			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define X3			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define X4			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)
#define X5			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)
#define X6			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0)
#define X7			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)
#define X8			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)
	
#define X9			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)
#define X10			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4)
#define X11			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5)
#define X12			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6)
#define X13			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7)
#define X14			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8)
#define X15			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9)
#define X16			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10)

#define X17			GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)
#define X18			GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define X19			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_11)
#define X20			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_12)
#define X21			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13)
#define X22			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_14)
#define X23			GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_15)
#define X24			GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_0)

#define X25			GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1)
#define X26			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)
#define X27			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)
#define X28			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)
#define X29			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)
#define X30			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)
#define X31			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)
#define X32			GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)


#define Y1        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)
#define Y1_ON     GPIO_ResetBits(GPIOD, GPIO_Pin_14)
#define Y1_OFF    GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define Y2        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)
#define Y2_ON     GPIO_ResetBits(GPIOD, GPIO_Pin_15)
#define Y2_OFF    GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define Y3        GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_2)
#define Y3_ON     GPIO_ResetBits(GPIOG, GPIO_Pin_2)
#define Y3_OFF    GPIO_SetBits(GPIOG, GPIO_Pin_2)
#define Y4        GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_3)
#define Y4_ON     GPIO_ResetBits(GPIOG, GPIO_Pin_3)
#define Y4_OFF    GPIO_SetBits(GPIOG, GPIO_Pin_3)
#define Y5        GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)
#define Y5_ON     GPIO_ResetBits(GPIOC, GPIO_Pin_7)
#define Y5_OFF    GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define Y6        GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8)
#define Y6_ON     GPIO_ResetBits(GPIOC, GPIO_Pin_8)
#define Y6_OFF    GPIO_SetBits(GPIOC, GPIO_Pin_8)
#define Y7        GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)
#define Y7_ON     GPIO_ResetBits(GPIOC, GPIO_Pin_9)
#define Y7_OFF    GPIO_SetBits(GPIOC, GPIO_Pin_9)
#define Y8        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define Y8_ON     GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define Y8_OFF    GPIO_SetBits(GPIOA, GPIO_Pin_8)


#define Y9       GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)
#define Y9_ON    GPIO_ResetBits(GPIOC, GPIO_Pin_6)
#define Y9_OFF   GPIO_SetBits(GPIOC, GPIO_Pin_6)
#define Y10       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_6)
#define Y10_ON    GPIO_ResetBits(GPIOG, GPIO_Pin_6)
#define Y10_OFF   GPIO_SetBits(GPIOG, GPIO_Pin_6)
#define Y11       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_5)
#define Y11_ON    GPIO_ResetBits(GPIOG, GPIO_Pin_5)
#define Y11_OFF   GPIO_SetBits(GPIOG, GPIO_Pin_5)
#define Y12        GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_4)
#define Y12_ON     GPIO_ResetBits(GPIOG, GPIO_Pin_4)
#define Y12_OFF    GPIO_SetBits(GPIOG, GPIO_Pin_4)

#define Y13       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_14)
#define Y13_ON    GPIO_ResetBits(GPIOG, GPIO_Pin_14)
#define Y13_OFF   GPIO_SetBits(GPIOG, GPIO_Pin_14)
#define Y14       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_13)
#define Y14_ON    GPIO_ResetBits(GPIOG, GPIO_Pin_13)
#define Y14_OFF   GPIO_SetBits(GPIOG, GPIO_Pin_13)
#define Y15       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_12)
#define Y15_ON    GPIO_ResetBits(GPIOG, GPIO_Pin_12)
#define Y15_OFF   GPIO_SetBits(GPIOG, GPIO_Pin_12)
#define Y16       GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)
#define Y16_ON    GPIO_ResetBits(GPIOD, GPIO_Pin_7)
#define Y16_OFF   GPIO_SetBits(GPIOD, GPIO_Pin_7)

#define PWR_ON    GPIO_SetBits(GPIOE, GPIO_Pin_14);GPIO_ResetBits(GPIOG, GPIO_Pin_15)
#define PWR_OFF   GPIO_ResetBits(GPIOG, GPIO_Pin_14);GPIO_SetBits(GPIOE, GPIO_Pin_15)


typedef union
{
    struct
    {
        unsigned X_1   : 1;
        unsigned X_2   : 1;
        unsigned X_3   : 1;
        unsigned X_4   : 1;
        unsigned X_5   : 1;
        unsigned X_6   : 1;
        unsigned X_7   : 1;
        unsigned X_8   : 1;

        unsigned X_9   : 1;
        unsigned X_10   : 1;
        unsigned X_11   : 1;
        unsigned X_12   : 1;
        unsigned X_13   : 1;
        unsigned X_14   : 1;
        unsigned X_15   : 1;
        unsigned X_16   : 1;
			
		unsigned X_17   : 1;
        unsigned X_18   : 1;
        unsigned X_19   : 1;
        unsigned X_20   : 1;
        unsigned X_21   : 1;
        unsigned X_22   : 1;
        unsigned X_23   : 1;
        unsigned X_24   : 1;
				
		unsigned X_25   : 1;
        unsigned X_26   : 1;
        unsigned X_27   : 1;
        unsigned X_28   : 1;
        unsigned X_29   : 1;
        unsigned X_30   : 1;
        unsigned X_31   : 1;
        unsigned X_32   : 1;
    }ONE;
    unsigned int ALL;
}Type_Input_Port;

extern Type_Input_Port Input_Port;

typedef union
{
    struct
    {
        unsigned Y_1   : 1;
        unsigned Y_2   : 1;
        unsigned Y_3   : 1;
        unsigned Y_4   : 1;
        unsigned Y_5   : 1;
        unsigned Y_6   : 1;
        unsigned Y_7   : 1;
        unsigned Y_8   : 1;

        unsigned Y_9   : 1;
        unsigned Y_10   : 1;
        unsigned Y_11   : 1;
        unsigned Y_12   : 1;
        unsigned Y_13   : 1;
        unsigned Y_14   : 1;
        unsigned Y_15   : 1;
        unsigned Y_16   : 1;
    }ONE;
    unsigned short ALL;
}Type_Output_Port;

extern Type_Output_Port Output_Port;

void GPIO_Config(void);
void OutputControl(unsigned int stats);
unsigned int InputRead(void);
unsigned int OutputRead(void);
//unsigned char Input_L_Value(unsigned int num);
//unsigned char Input_H_Value(unsigned int num);


#ifdef __cplusplus		  
}
#endif

#endif
