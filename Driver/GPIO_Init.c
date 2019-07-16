#include "GPIO_Init.h"
#include "platform_config.h"

Type_Line_A_Port Line_A_Port;
Type_Line_B_Port Line_B_Port;
/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|
                            RCC_APB2Periph_GPIOB|
                            RCC_APB2Periph_GPIOC|
                            RCC_APB2Periph_GPIOD|
                            RCC_APB2Periph_GPIOE|
                            RCC_APB2Periph_GPIOF|
                            RCC_APB2Periph_GPIOG|
                            RCC_APB2Periph_AFIO, ENABLE);		//开时钟
	
    //LED														 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;									
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOA, &GPIO_InitStructure);		
	//Btn
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;									
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//端口模式为上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;									
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13  |GPIO_Pin_14 |GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //拨码开关 Status
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14;		//ID1 ID2							
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//端口模式为上拉输入方式	
//    GPIO_Init(GPIOB, &GPIO_InitStructure);     
}



/*******************************************************************************
* Function Name  :
* Description    : 控制外部输出
********************************************************************************/

void Line_A_Control(int stats)
{
    Line_A_Port.ALL=stats;

    if(Line_A_Port.ONE.A_1==1)
    { A1_ON; }
    else
    { A1_OFF;}

    if(Line_A_Port.ONE.A_2==1)
    { A2_ON; }
    else
    { A2_OFF;}

    if(Line_A_Port.ONE.A_3==1)
    { A3_ON; }
    else
    { A3_OFF;}
    if(Line_A_Port.ONE.A_4==1)
    { A4_ON; }
    else
    { A4_OFF;}

    if(Line_A_Port.ONE.A_5==1)
    { A5_ON; }
    else
    { A5_OFF;}

    if(Line_A_Port.ONE.A_6==1)
    { A6_ON; }
    else
    { A6_OFF;}
     if(Line_A_Port.ONE.A_7==1)
    { A7_ON; }
    else
    { A7_OFF;}

    if(Line_A_Port.ONE.A_8==1)
    { A8_ON; }
    else
    { A8_OFF;}

    if(Line_A_Port.ONE.A_9==1)
    { A9_ON; }
    else
    { A9_OFF;}
    if(Line_A_Port.ONE.A_10==1)
    { A10_ON; }
    else
    { A10_OFF;}

    if(Line_A_Port.ONE.A_11==1)
    { A11_ON; }
    else
    { A11_OFF;}

    if(Line_A_Port.ONE.A_12==1)
    { A12_ON; }
    else
    { A12_OFF;}

    if(Line_A_Port.ONE.A_13==1)
    { A13_ON; }
    else
    { A13_OFF;}
    if(Line_A_Port.ONE.A_14==1)
    { A14_ON; }
    else
    { A14_OFF;}
    if(Line_A_Port.ONE.A_15==1)
    { A15_ON; }
    else
    { A15_OFF;}
    if(Line_A_Port.ONE.A_16==1)
    { A16_ON; }
    else
    { A16_OFF;}
		if(Line_A_Port.ONE.A_17==1)
    { A17_ON; }
    else
    { A17_OFF;}
		if(Line_A_Port.ONE.A_18==1)
    { A18_ON; }
    else
    { A18_OFF;}
		if(Line_A_Port.ONE.A_19==1)
    { A19_ON; }
    else
    { A19_OFF;}
		if(Line_A_Port.ONE.A_20==1)
    { A20_ON; }
    else
    { A20_OFF;}
}



void Line_B_Control(int stats)
{
    Line_B_Port.ALL=stats;

		
		if(Line_B_Port.ONE.B_1==1)
    { B1_ON; }
    else
    { B1_OFF;}

    if(Line_B_Port.ONE.B_2==1)
    { B2_ON; }
    else
    { B2_OFF;}

    if(Line_B_Port.ONE.B_3==1)
    { B3_ON; }
    else
    { B3_OFF;}
    if(Line_B_Port.ONE.B_4==1)
    { B4_ON; }
    else
    { B4_OFF;}

    if(Line_B_Port.ONE.B_5==1)
    { B5_ON; }
    else
    { B5_OFF;}

    if(Line_B_Port.ONE.B_6==1)
    { B6_ON; }
    else
    { B6_OFF;}
     if(Line_B_Port.ONE.B_7==1)
    { B7_ON; }
    else
    { B7_OFF;}

    if(Line_B_Port.ONE.B_8==1)
    { B8_ON; }
    else
    { B8_OFF;}

    if(Line_B_Port.ONE.B_9==1)
    { B9_ON; }
    else
    { B9_OFF;}
    if(Line_B_Port.ONE.B_10==1)
    { B10_ON; }
    else
    { B10_OFF;}

    if(Line_B_Port.ONE.B_11==1)
    { B11_ON; }
    else
    { B11_OFF;}

    if(Line_B_Port.ONE.B_12==1)
    { B12_ON; }
    else
    { B12_OFF;}

    if(Line_B_Port.ONE.B_13==1)
    { B13_ON; }
    else
    { B13_OFF;}
    if(Line_B_Port.ONE.B_14==1)
    { B14_ON; }
    else
    { B14_OFF;}
    if(Line_B_Port.ONE.B_15==1)
    { B15_ON; }
    else
    { B15_OFF;}
    if(Line_B_Port.ONE.B_16==1)
    { B16_ON; }
    else
    { B16_OFF;}
		if(Line_B_Port.ONE.B_17==1)
    { B17_ON; }
    else
    { B17_OFF;}
		if(Line_B_Port.ONE.B_18==1)
    { B18_ON; }
    else
    { B18_OFF;}
		if(Line_B_Port.ONE.B_19==1)
    { B19_ON; }
    else
    { B19_OFF;}
		if(Line_B_Port.ONE.B_20==1)
    { B20_ON; }
    else
    { B20_OFF;}
}













