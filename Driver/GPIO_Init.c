#include "GPIO_Init.h"
#include "platform_config.h"

Type_Input_Port Input_Port ;
Type_Output_Port Output_Port ;
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
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;									
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOA, &GPIO_InitStructure);			
    //Power Control
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 |GPIO_Pin_15;									
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOE, &GPIO_InitStructure);	
    
    //Power IN Status
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;									
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//端口模式为上拉输入方式	
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
    
    //拨码开关 Status
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;									
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//端口模式为上拉输入方式	
    GPIO_Init(GPIOD, &GPIO_InitStructure); 
    
    //Input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 ;									
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//端口模式为上拉输入方式	
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 ;									
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//端口模式为上拉输入方式	
    GPIO_Init(GPIOG, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |
                                    GPIO_Pin_2 |GPIO_Pin_3 |
                                    GPIO_Pin_4 |GPIO_Pin_5 |
                                    GPIO_Pin_6 |GPIO_Pin_7 |
                                    GPIO_Pin_8 |GPIO_Pin_9 |
                                    GPIO_Pin_10|GPIO_Pin_11|
                                    GPIO_Pin_12|GPIO_Pin_13|
                                    GPIO_Pin_14|GPIO_Pin_15;									
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//端口模式为上拉输入方式	
    GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3 |
                                    GPIO_Pin_4 |GPIO_Pin_5 |
                                    GPIO_Pin_6 |GPIO_Pin_7 |
                                    GPIO_Pin_8 |GPIO_Pin_9 |
                                    GPIO_Pin_10|GPIO_Pin_11|
                                    GPIO_Pin_12|GPIO_Pin_13;									
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//端口模式为上拉输入方式	
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    //Output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;									
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOA, &GPIO_InitStructure);	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_14 |GPIO_Pin_15;									
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;								
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14;										
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOG, &GPIO_InitStructure);
}



/*******************************************************************************
* Function Name  :
* Description    : 控制外部输出
********************************************************************************/

void OutputControl(unsigned int stats)
{
    Output_Port.ALL=stats;

    if(Output_Port.ONE.Y_1==1)
    { Y1_ON; }
    else
    { Y1_OFF;}

    if(Output_Port.ONE.Y_2==1)
    { Y2_ON; }
    else
    { Y2_OFF;}

    if(Output_Port.ONE.Y_3==1)
    { Y3_ON; }
    else
    { Y3_OFF;}
    if(Output_Port.ONE.Y_4==1)
    { Y4_ON; }
    else
    { Y4_OFF;}

    if(Output_Port.ONE.Y_5==1)
    { Y5_ON; }
    else
    { Y5_OFF;}

    if(Output_Port.ONE.Y_6==1)
    { Y6_ON; }
    else
    { Y6_OFF;}
     if(Output_Port.ONE.Y_7==1)
    { Y7_ON; }
    else
    { Y7_OFF;}

    if(Output_Port.ONE.Y_8==1)
    { Y8_ON; }
    else
    { Y8_OFF;}

    if(Output_Port.ONE.Y_9==1)
    { Y9_ON; }
    else
    { Y9_OFF;}
    if(Output_Port.ONE.Y_10==1)
    { Y10_ON; }
    else
    { Y10_OFF;}

    if(Output_Port.ONE.Y_11==1)
    { Y11_ON; }
    else
    { Y11_OFF;}

    if(Output_Port.ONE.Y_12==1)
    { Y12_ON; }
    else
    { Y12_OFF;}

    if(Output_Port.ONE.Y_13==1)
    { Y13_ON; }
    else
    { Y13_OFF;}
    if(Output_Port.ONE.Y_14==1)
    { Y14_ON; }
    else
    { Y14_OFF;}
    if(Output_Port.ONE.Y_15==1)
    { Y15_ON; }
    else
    { Y15_OFF;}
    if(Output_Port.ONE.Y_16==1)
    { Y16_ON; }
    else
    { Y16_OFF;}
}

/*******************************************************************************
* Function Name  :
* Description    : 读取输入状态 0L 1H
********************************************************************************/
unsigned int InputRead(void)
{
    Input_Port.ALL=0;           //清空

		if(X1==1)
		{ Input_Port.ONE.X_1=1; }
		else
		{ Input_Port.ONE.X_1=0; }

		if(X2==1)
		{ Input_Port.ONE.X_2=1; }
		else
		{ Input_Port.ONE.X_2=0; }

		if(X3==1)
		{ Input_Port.ONE.X_3=1; }
		else
		{ Input_Port.ONE.X_3=0; }

		if(X4==1)
		{ Input_Port.ONE.X_4=1; }
		else
		{ Input_Port.ONE.X_4=0; }
		
		if(X5==1)
		{ Input_Port.ONE.X_5=1; }
		else
		{ Input_Port.ONE.X_5=0; }

		if(X6==1)
		{ Input_Port.ONE.X_6=1; }
		else
		{ Input_Port.ONE.X_6=0; }

		if(X7==1)
		{ Input_Port.ONE.X_7=1; }
		else
		{ Input_Port.ONE.X_7=0; }

		if(X8==1)
		{ Input_Port.ONE.X_8=1; }
		else
		{ Input_Port.ONE.X_8=0; }

		if(X9==1)
		{ Input_Port.ONE.X_9=1; }
		else
		{ Input_Port.ONE.X_9=0; }

		if(X10==1)
		{ Input_Port.ONE.X_10=1; }
		else
		{ Input_Port.ONE.X_10=0; }

		if(X11==1)
		{ Input_Port.ONE.X_11=1; }
		else
		{ Input_Port.ONE.X_11=0; }

		if(X12==1)
		{ Input_Port.ONE.X_12=1; }
		else
		{ Input_Port.ONE.X_12=0; }

		if(X13==1)
		{ Input_Port.ONE.X_13=1; }
		else
		{ Input_Port.ONE.X_13=0; }

		if(X14==1)
		{ Input_Port.ONE.X_14=1; }
		else
		{ Input_Port.ONE.X_14=0; }

		if(X15==1)
		{ Input_Port.ONE.X_15=1; }
		else
		{ Input_Port.ONE.X_15=0; }

		if(X16==1)
		{ Input_Port.ONE.X_16=1; }
		else
		{ Input_Port.ONE.X_16=0; }

		if(X17==1)
		{ Input_Port.ONE.X_17=1; }
		else
		{ Input_Port.ONE.X_17=0; }

		if(X18==1)
		{ Input_Port.ONE.X_18=1; }
		else
		{ Input_Port.ONE.X_18=0; }

		if(X19==1)
		{ Input_Port.ONE.X_19=1; }
		else
		{ Input_Port.ONE.X_19=0; }

		if(X20==1)
		{ Input_Port.ONE.X_20=1; }
		else
		{ Input_Port.ONE.X_20=0; }

		if(X21==1)
		{ Input_Port.ONE.X_21=1; }
		else
		{ Input_Port.ONE.X_21=0; }

		if(X22==1)
		{ Input_Port.ONE.X_22=1; }
		else
		{ Input_Port.ONE.X_22=0; }

		if(X23==1)
		{ Input_Port.ONE.X_23=1; }
		else
		{ Input_Port.ONE.X_23=0; }

		if(X24==1)
		{ Input_Port.ONE.X_24=1; }
		else
		{ Input_Port.ONE.X_24=0; }
		if(X25==1)
		{ Input_Port.ONE.X_25=1; }
		else
		{ Input_Port.ONE.X_25=0; }

		if(X26==1)
		{ Input_Port.ONE.X_26=1; }
		else
		{ Input_Port.ONE.X_26=0; }

		if(X27==1)
		{ Input_Port.ONE.X_27=1; }
		else
		{ Input_Port.ONE.X_27=0; }

		if(X28==1)
		{ Input_Port.ONE.X_28=1; }
		else
		{ Input_Port.ONE.X_28=0; }
		if(X29==1)
		{ Input_Port.ONE.X_29=1; }
		else
		{ Input_Port.ONE.X_29=0; }

		if(X30==1)
		{ Input_Port.ONE.X_30=1; }
		else
		{ Input_Port.ONE.X_30=0; }

		if(X31==1)
		{ Input_Port.ONE.X_31=1; }
		else
		{ Input_Port.ONE.X_31=0; }

		if(X32==1)
		{ Input_Port.ONE.X_32=1; }
		else
		{ Input_Port.ONE.X_32=0; }

   return ~Input_Port.ALL;
}
   /*******************************************************************************
* Function Name  :
* Description    :读取输出状态
********************************************************************************/
unsigned int OutputRead(void)
{

        if(Y1==1)
        { Output_Port.ONE.Y_1=1; }
        else
        { Output_Port.ONE.Y_1=0; }

        if(Y2==1)
        { Output_Port.ONE.Y_2=1; }
        else
        { Output_Port.ONE.Y_2=0; }

        if(Y3==1)
        { Output_Port.ONE.Y_3=1; }
        else
        { Output_Port.ONE.Y_3=0; }

        if(Y4==1)
        { Output_Port.ONE.Y_4=1; }
        else
        { Output_Port.ONE.Y_4=0; }

        if(Y5==1)
        { Output_Port.ONE.Y_5=1; }
        else
        { Output_Port.ONE.Y_5=0; }

        if(Y6==1)
        { Output_Port.ONE.Y_6=1; }
        else
        { Output_Port.ONE.Y_6=0; }

        if(Y7==1)
        { Output_Port.ONE.Y_7=1; }
        else
        { Output_Port.ONE.Y_7=0; }

        if(Y8==1)
        { Output_Port.ONE.Y_8=1; }
        else
        { Output_Port.ONE.Y_8=0; }

        if(Y9==1)
        { Output_Port.ONE.Y_9=1; }
        else
        { Output_Port.ONE.Y_9=0;}


        if(Y10==1)
        { Output_Port.ONE.Y_10=1; }
        else
        { Output_Port.ONE.Y_10=0; }

        if(Y11==1)
        { Output_Port.ONE.Y_11=1; }
        else
        { Output_Port.ONE.Y_11=0; }

        if(Y12==1)
        { Output_Port.ONE.Y_12=1; }
        else
        { Output_Port.ONE.Y_12=0; }

        if(Y13==1)
        { Output_Port.ONE.Y_13=1; }
        else
        { Output_Port.ONE.Y_13=0; }

        if(Y14==1)
        { Output_Port.ONE.Y_14=1; }
        else
        { Output_Port.ONE.Y_14=0; }

        if(Y15==1)
        { Output_Port.ONE.Y_15=1; }
        else
        { Output_Port.ONE.Y_15=0; }

        if(Y16==1)
        { Output_Port.ONE.Y_16=1; }
        else
        { Output_Port.ONE.Y_16=0; }


    return ~Output_Port.ALL;
}

///*******************************************************************************
// * 输入低位是否使能 返回宏定义的值
///*******************************************************************************/
//unsigned char Input_L_Value(unsigned int num)
//{
//	switch(num)                     //返回指定通道的电平
//	{
//			case 0x0001: return X1;
//			case 0x0002: return X2;
//			case 0x0004: return X3;
//			case 0x0008: return X4;
//			case 0x0010: return X5;
//			case 0x0020: return X6;
//			case 0x0040: return X7;
//			case 0x0080: return X8;
//			case 0x0100: return X9;
//			default: break;    
//	}
//}


///*******************************************************************************
// * 输入高位位是否使能 返回宏定义的值
///*******************************************************************************/
//unsigned char Input_H_Value(unsigned int num)
//{
//  switch(num)                     //返回指定通道的电平
//	{
//			case 0x0002: return X18;
//			case 0x0004: return X19;
//			case 0x0008: return X20;
//			case 0x0010: return X21;
//			case 0x0020: return X22;
//			case 0x0040: return X23;
//			default: break;
//	}
//}
