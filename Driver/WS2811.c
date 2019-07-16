/****************************************************************************************
* WS2811 �ʵ���������
*
* ���÷�����
*	�޸ĺ궨�壺 #define nWs 1	// �ж��ٿ�WS2811����
*	WS_Init();	// IO��ʼ��
*	WsDat[0] = 0x808080;//�Դ渳ֵ
*	WS_SetAll();  // ��������
*	ColorToColor(unsigned long color0, unsigned long color1);// ��ɫ�����㷨
*
* ���ߣ���ϣ������У�飩
* ���ڣ�2015��6��24��
****************************************************************************************/
//#include "sys.h"
//#include <stm32f10x.h>
#include "WS2811.h"
//#include "delay.h"
	
/* �Դ� */
unsigned long WsDat[nWs] = {0x00ff00};
unsigned long RGB_DISP[24] = {0x000000,0xDC143C,0xFF1493,0xFF00FF,0x800080,0x4B0082,0x7B68EE,0x0000FF,
							  0x4169E1,0x1E90FF,0x00BFFF,0x00FFFF,0x00FF7F,0x00FF00,0x7FFF00,0xADFF2F,
							  0xFFFF00,0xFFD700,0xFFA500,0xFF4500,0xFF0000,0x8B0000,0xFF00FF,0x800080};

/**************************************************************************************
* IO��ʼ������ֲʱ���޸ģ�
**************************************************************************************/
void WS_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	
	//�˿�ʱ�ӣ�ʹ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );	 

	// �˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				// PIN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					// �����趨������ʼ�� 
}

/**************************
* �ڲ���ʱ
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
* ����һ����
****************************/
void TX0(void)  	
{ 
	PBout(10) = 1; 
	delay05us(); 	
	PBout(10) = 0; 
	delay2us(); 
} // ����0
void TX1(void)  	
{ 
	PBout(10) = 1; 
	delay2us();  	
	PBout(10) = 0; 
	delay05us(); 
} // ����1
void WS_Reset(void) 
{ 
	PBout(10) = 0; 
	Delay_US(200);  
}

/**************************************************************************************
* ����һ�ֽ�
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
		dat<<=1;							//����һλ
	}
}

/**************************************************************************************
* ���������ֽ�
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
* �����ֵ
********************************************/
unsigned char abs0(int num)
{
	if(num>0) return num;
	
	num = -num;
	return (unsigned char) num;
}

/***********************************************************************************
* ��ɫ�����㷨
* ��� <= 2
************************************************************************************/
u32 ColorToColor(unsigned long color0, unsigned long color1)
{
	unsigned char Red0, Green0, Blue0;  // ��ʼ��ԭɫ
	unsigned char Red1, Green1, Blue1;  // �����ԭɫ
	int			  RedMinus, GreenMinus, BlueMinus;	// ��ɫ�color1 - color0��
	unsigned char NStep; 							// ��Ҫ����
	float		  RedStep, GreenStep, BlueStep;		// ��ɫ����ֵ
	unsigned long color;							// ���ɫ
	unsigned char i;
	
	// �� �� �� ��ԭɫ�ֽ�
	Red0   = color0>>8;
	Green0 = color0>>16;
	Blue0  = color0;
	
	Red1   = color1>>8;
	Green1 = color1>>16;
	Blue1  = color1;
	
	// ������Ҫ���ٲ���ȡ��ֵ�����ֵ��
	RedMinus   = Red1 - Red0; 
	GreenMinus = Green1 - Green0; 
	BlueMinus  = Blue1 - Blue0;
	
	NStep = ( abs0(RedMinus) > abs0(GreenMinus) ) ? abs0(RedMinus):abs0(GreenMinus);
	NStep = ( NStep > abs0(BlueMinus) ) ? NStep:abs0(BlueMinus);
	
	// �������ɫ����ֵ
	RedStep   = (float)RedMinus   / NStep;
	GreenStep = (float)GreenMinus / NStep;
	BlueStep  = (float)BlueMinus  / NStep;
	
	// ���俪ʼ
	for(i=0; i<NStep; i++)
	{
		Red1   = Red0   + (int)(RedStep   * i);
		Green1 = Green0 + (int)(GreenStep * i);
		Blue1  = Blue0  + (int)(BlueStep  * i);
		
		color  = Green1<<16 | Red1<<8 | Blue1; 	// �ϳ�  �̺���
		WsDat[0] = color;
		WS_SetAll();							// ���
		Delay_MS(1);						// �����ٶ�
	}
	// �������
	
	return color;
}










