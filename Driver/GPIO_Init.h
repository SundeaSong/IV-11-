#ifndef _GPIO_INIT_H_	
#define _GPIO_INIT_H_

#ifdef __cplusplus			//定义对CPP进行C处理
extern "C" {
#endif

#include "Config.h"

#define ON  0
#define OFF 1

#define SW_ID_0       GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)
#define SW_ID_1       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9)
#define SW_ID_2       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_10)	


#define A1        GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define A1_ON     GPIO_ResetBits(GPIOE, GPIO_Pin_2)
#define A1_OFF    GPIO_SetBits(GPIOE, GPIO_Pin_2)
#define A2        GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define A2_ON     GPIO_ResetBits(GPIOE, GPIO_Pin_3)
#define A2_OFF    GPIO_SetBits(GPIOE, GPIO_Pin_3)
#define A3        GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define A3_ON     GPIO_ResetBits(GPIOE, GPIO_Pin_4)
#define A3_OFF    GPIO_SetBits(GPIOE, GPIO_Pin_4)
#define A4        GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)
#define A4_ON     GPIO_ResetBits(GPIOE, GPIO_Pin_5)
#define A4_OFF    GPIO_SetBits(GPIOE, GPIO_Pin_5)
#define A5        GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)
#define A5_ON     GPIO_ResetBits(GPIOE, GPIO_Pin_6)
#define A5_OFF    GPIO_SetBits(GPIOE, GPIO_Pin_6)
#define A6        GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15)
#define A6_ON     GPIO_ResetBits(GPIOC, GPIO_Pin_15)
#define A6_OFF    GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define A7        GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0)
#define A7_ON     GPIO_ResetBits(GPIOF, GPIO_Pin_0)
#define A7_OFF    GPIO_SetBits(GPIOF, GPIO_Pin_0)
#define A8        GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)
#define A8_ON     GPIO_ResetBits(GPIOF, GPIO_Pin_1)
#define A8_OFF    GPIO_SetBits(GPIOF, GPIO_Pin_1)
#define A9       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)
#define A9_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_2)
#define A9_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_2)
#define A10       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)
#define A10_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_3)
#define A10_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_3)

#define A11       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4)
#define A11_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_4)
#define A11_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_4)
#define A12        GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5)
#define A12_ON     GPIO_ResetBits(GPIOF, GPIO_Pin_5)
#define A12_OFF    GPIO_SetBits(GPIOF, GPIO_Pin_5)
#define A13       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6)
#define A13_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_6)
#define A13_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_6)
#define A14       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7)
#define A14_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_7)
#define A14_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_7)
#define A15       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8)
#define A15_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_8)
#define A15_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_8)
#define A16       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9)
#define A16_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_9)
#define A16_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_9)
#define A17       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10)
#define A17_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_10)
#define A17_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_10)
#define A18       GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define A18_ON    GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define A18_OFF   GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define A19       GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define A19_ON    GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define A19_OFF   GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define A20       GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)
#define A20_ON    GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define A20_OFF   GPIO_SetBits(GPIOA, GPIO_Pin_2)

#define B1        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define B1_ON     GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define B1_OFF    GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define B2        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)
#define B2_ON     GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define B2_OFF    GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define B3        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)
#define B3_ON     GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define B3_OFF    GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define B4        GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)
#define B4_ON     GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define B4_OFF    GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define B5        GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)
#define B5_ON     GPIO_ResetBits(GPIOC, GPIO_Pin_5)
#define B5_OFF    GPIO_SetBits(GPIOC, GPIO_Pin_5)
#define B6        GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)
#define B6_ON     GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define B6_OFF    GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define B7        GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define B7_ON     GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define B7_OFF    GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define B8        GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_11)
#define B8_ON     GPIO_ResetBits(GPIOF, GPIO_Pin_11)
#define B8_OFF    GPIO_SetBits(GPIOF, GPIO_Pin_11)
#define B9       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_12)
#define B9_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_12)
#define B9_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_12)
#define B10       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13)
#define B10_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_13)
#define B10_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_13)


#define B11       GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_14)
#define B11_ON    GPIO_ResetBits(GPIOF, GPIO_Pin_14)
#define B11_OFF   GPIO_SetBits(GPIOF, GPIO_Pin_14)
#define B12        GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_15)
#define B12_ON     GPIO_ResetBits(GPIOF, GPIO_Pin_15)
#define B12_OFF    GPIO_SetBits(GPIOF, GPIO_Pin_15)
#define B13       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_0)
#define B13_ON    GPIO_ResetBits(GPIOG, GPIO_Pin_0)
#define B13_OFF   GPIO_SetBits(GPIOG, GPIO_Pin_0)
#define B14       GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1)
#define B14_ON    GPIO_ResetBits(GPIOG, GPIO_Pin_1)
#define B14_OFF   GPIO_SetBits(GPIOG, GPIO_Pin_1)
#define B15       GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)
#define B15_ON    GPIO_ResetBits(GPIOE, GPIO_Pin_7)
#define B15_OFF   GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define B16       GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)
#define B16_ON    GPIO_ResetBits(GPIOE, GPIO_Pin_8)
#define B16_OFF   GPIO_SetBits(GPIOE, GPIO_Pin_8)
#define B17       GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)
#define B17_ON    GPIO_ResetBits(GPIOE, GPIO_Pin_9)
#define B17_OFF   GPIO_SetBits(GPIOE, GPIO_Pin_9)
#define B18       GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10)
#define B18_ON    GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define B18_OFF   GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define B19       GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)
#define B19_ON    GPIO_ResetBits(GPIOE, GPIO_Pin_11)
#define B19_OFF   GPIO_SetBits(GPIOE, GPIO_Pin_11)
#define B20       GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)
#define B20_ON    GPIO_ResetBits(GPIOE, GPIO_Pin_12)
#define B20_OFF   GPIO_SetBits(GPIOE, GPIO_Pin_12)

//#define PWR_ON    GPIO_SetBits(GPIOE, GPIO_Pin_14);GPIO_ResetBits(GPIOG, GPIO_Pin_15)
//#define PWR_OFF   GPIO_ResetBits(GPIOG, GPIO_Pin_14);GPIO_SetBits(GPIOE, GPIO_Pin_15)


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
        unsigned A_1   : 1;
        unsigned A_2   : 1;
        unsigned A_3   : 1;
        unsigned A_4   : 1;
        unsigned A_5   : 1;
        unsigned A_6   : 1;
        unsigned A_7   : 1;
        unsigned A_8   : 1;
        unsigned A_9   : 1;
        unsigned A_10   : 1;
			
        unsigned A_11   : 1;
        unsigned A_12   : 1;
        unsigned A_13   : 1;
        unsigned A_14   : 1;
        unsigned A_15   : 1;
        unsigned A_16   : 1;
				unsigned A_17   : 1;
        unsigned A_18   : 1;
        unsigned A_19   : 1;
        unsigned A_20   : 1;

    }ONE;
    unsigned int ALL;
}Type_Line_A_Port;

extern Type_Line_A_Port Line_A_Port;

typedef union
{
    struct
    {
				unsigned B_1   : 1;
        unsigned B_2   : 1;
        unsigned B_3   : 1;
        unsigned B_4   : 1;
        unsigned B_5   : 1;
        unsigned B_6   : 1;
        unsigned B_7   : 1;
        unsigned B_8   : 1;
        unsigned B_9   : 1;
        unsigned B_10   : 1;
			
        unsigned B_11   : 1;
        unsigned B_12   : 1;
        unsigned B_13   : 1;
        unsigned B_14   : 1;
        unsigned B_15   : 1;
        unsigned B_16   : 1;
				unsigned B_17   : 1;
        unsigned B_18   : 1;
				unsigned B_19   : 1;
        unsigned B_20   : 1;
				
    }ONE;
    unsigned int ALL;
}Type_Line_B_Port;

extern Type_Line_B_Port Line_B_Port;

void GPIO_Config(void);
//void OutputControl(unsigned int stats);
void Line_A_Control(int stats);
void Line_B_Control(int stats);
//unsigned char Input_L_Value(unsigned int num);
//unsigned char Input_H_Value(unsigned int num);


#ifdef __cplusplus		  
}
#endif

#endif
