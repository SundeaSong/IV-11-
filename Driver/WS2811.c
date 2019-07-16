/****************************************************************************************
* WS2811 彩灯驱动函数
*
* 调用方法：
*	修改宏定义： #define nWs 1	// 有多少颗WS2811级联
*	WS_Init();	// IO初始化
*	WsDat[0] = 0x808080;//显存赋值
*	WS_SetAll();  // 发送数据
*	ColorToColor(unsigned long color0, unsigned long color1);// 颜色渐变算法
*
* 作者：星希望（已校验）
* 日期：2015年6月24日
****************************************************************************************/
//#include "sys.h"
//#include <stm32f10x.h>
#include "WS2811.h"
//#include "delay.h"
	
/* 显存 */
unsigned long WsDat[nWs] = {0x00ff00};
unsigned long RGB_DISP[24] = {0x000000,0xDC143C,0xFF1493,0xFF00FF,0x800080,0x4B0082,0x7B68EE,0x0000FF,
							  0x4169E1,0x1E90FF,0x00BFFF,0x00FFFF,0x00FF7F,0x00FF00,0x7FFF00,0xADFF2F,
							  0xFFFF00,0xFFD700,0xFFA500,0xFF4500,0xFF0000,0x8B0000,0xFF00FF,0x800080};

/**************************************************************************************
* IO初始化（移植时请修改）
**************************************************************************************/
void WS_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	
	//端口时钟，使能
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );	 

	// 端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				// PIN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					// 根据设定参数初始化 
}

/**************************
* 内部延时
***************************/
void delay2us(void)
{
	delay05us();
	delay05us();
	delay05us();
//	delay05us();
//	_nop;
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); 
//	unsigned char i;
//	for(i=0; i<12; i++);
}
void delay05us(void)
{
	__NOP(); __NOP();// __NOP(); __NOP(); __NOP(); __NOP(); 
}


/***************************
* 发送一比特
****************************/
void TX0(void)  	
{ 
	PBout(10) = 1; 
	delay05us(); 	
	PBout(10) = 0; 
	delay2us(); 
} // 发送0
void TX1(void)  	
{ 
	PBout(10) = 1; 
	delay2us();  	
	PBout(10) = 0; 
	delay05us(); 
} // 发送1
void WS_Reset(void) 
{ 
	PBout(10) = 0; 
	Delay_US(200);  
}

/**************************************************************************************
* 发送一字节
**************************************************************************************/
void WS_Set1(unsigned long dat)
{
	unsigned char i;
	for(i=0; i<24; i++)
	{
		if(0x800000 == (dat & 0x800000) )	
		{
			TX1();
		}
		else	
		{			
			TX0();
		}
		dat<<=1;							//左移一位
	}
}

/**************************************************************************************
* 发送所有字节
**************************************************************************************/
void WS_SetAll(void)
{
	unsigned char j;
	
	for(j=0; j<nWs; j++)
	{
		WS_Set1(WsDat[0]);  // j / 0
	}
	WS_Reset();
}


void RGB_Disp(void)
{
	u8 i,j;
	for(i = 0; i < 24; i++)
	{
		for(j = 0; j <12; j++)
		{
		WS_Set1(RGB_DISP[i]);
		}
		WS_Reset();
		Delay_MS(500);
	}
}






/********************************************
* 求绝对值
********************************************/
unsigned char abs0(int num)
{
	if(num>0) return num;
	
	num = -num;
	return (unsigned char) num;
}

/***********************************************************************************
* 颜色渐变算法
* 误差 <= 2
************************************************************************************/
u32 ColorToColor(unsigned long color0, unsigned long color1)
{
	unsigned char Red0, Green0, Blue0;  // 起始三原色
	unsigned char Red1, Green1, Blue1;  // 结果三原色
	int			  RedMinus, GreenMinus, BlueMinus;	// 颜色差（color1 - color0）
	unsigned char NStep; 							// 需要几步
	float		  RedStep, GreenStep, BlueStep;		// 各色步进值
	unsigned long color;							// 结果色
	unsigned char i;
	
	// 绿 红 蓝 三原色分解
	Red0   = color0>>8;
	Green0 = color0>>16;
	Blue0  = color0;
	
	Red1   = color1>>8;
	Green1 = color1>>16;
	Blue1  = color1;
	
	// 计算需要多少步（取差值的最大值）
	RedMinus   = Red1 - Red0; 
	GreenMinus = Green1 - Green0; 
	BlueMinus  = Blue1 - Blue0;
	
	NStep = ( abs0(RedMinus) > abs0(GreenMinus) ) ? abs0(RedMinus):abs0(GreenMinus);
	NStep = ( NStep > abs0(BlueMinus) ) ? NStep:abs0(BlueMinus);
	
	// 计算出各色步进值
	RedStep   = (float)RedMinus   / NStep;
	GreenStep = (float)GreenMinus / NStep;
	BlueStep  = (float)BlueMinus  / NStep;
	
	// 渐变开始
	for(i=0; i<NStep; i++)
	{
		Red1   = Red0   + (int)(RedStep   * i);
		Green1 = Green0 + (int)(GreenStep * i);
		Blue1  = Blue0  + (int)(BlueStep  * i);
		
		color  = Green1<<16 | Red1<<8 | Blue1; 	// 合成  绿红蓝
		WsDat[0] = color;
		WS_SetAll();							// 输出
		Delay_MS(1);						// 渐变速度
	}
	// 渐变结束
	
	return color;
}










