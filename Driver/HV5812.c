#include "hv5812.h"
//											  a
//	YA	OUT1		S9	OUT17			|-----------|
//	YB	OUT2		S8	OUT16			|			|
//	YC	OUT3		S7	OUT15		f	|			|	b
//	YD	OUT4		S6	OUT14			|			|
//	YE	OUT5		S5	OUT13			|-----------|
//	YF	OUT6		S4	OUT12			|	  g		|
//	YG	OUT7		S3	OUT11		e	|			|	c
//	YH	OUT8		S2	OUT10			|			|
//	阳极			S1	OUT9			|-----------|  . dp
//					栅极					  d

unsigned char Numb_off[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};	//全OFF
//unsigned char Numb_on[]  = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1};	//全ON
					   //a,b,c,d,e,f,g,dp
unsigned char Numb1[] = {0,0,0,0,0,1,1,0};	//数字1		0x08
unsigned char Numb2[] = {0,0,0,1,1,0,1,1};	//数字2 	0x60
unsigned char Numb3[] = {0,1,0,0,1,1,1,1};	//数字3		0x2f
unsigned char Numb4[] = {0,1,1,0,0,1,1,0};	//数字4		0x6d
unsigned char Numb5[] = {0,1,1,0,1,1,0,1};	//数字5		0x5d
unsigned char Numb6[] = {0,1,1,1,1,1,0,1};	//数字6		0x3f
unsigned char Numb7[] = {0,0,0,0,0,1,1,1};	//数字7		0x61
unsigned char Numb8[] = {0,1,1,1,1,1,1,1};	//数字8		0x7f
unsigned char Numb9[] = {0,1,1,0,1,1,1,1};	//数字9		0x7d
unsigned char Numb0[] = {0,0,1,1,1,1,1,1};	//数字0		0x77
											//小数点	0x80

					   //9,8,7,6,5,4,3,2,1	从右往左数
unsigned char wei8[]  = {1,0,0,0,0,0,0,0,0};	//符号
unsigned char wei7[]  = {0,1,0,0,0,0,0,0,0};
unsigned char wei6[]  = {0,0,1,0,0,0,0,0,0};
unsigned char wei5[]  = {0,0,0,1,0,0,0,0,0};
unsigned char wei4[]  = {0,0,0,0,1,0,0,0,0};
unsigned char wei3[]  = {0,0,0,0,0,1,0,0,0};
unsigned char wei2[]  = {0,0,0,0,0,0,1,0,0};
unsigned char wei1[]  = {0,0,0,0,0,0,0,1,0};
unsigned char wei0[]  = {0,0,0,0,0,0,0,0,1};
//unsigned char wei9[]  = {};
//unsigned char wei10[]  = {};

void HV5812_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);		//开时钟
													 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;									
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;									
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//时钟速度为50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//端口模式为推拉输出方式	
    GPIO_Init(GPIOB, &GPIO_InitStructure);		
}

void hv5812_init(void)
{
	HV5812_Config();
	Din_OFF;
	Delay_US(2);
	Clock_OFF;
	Delay_US(2);
	Blank_OFF;
	Delay_US(2);
	printf("HV5812_Init_OK\r\n");
}

void hv5812_data(unsigned int data,unsigned char num)
{
	uint8_t i,temp;
	for(i = 0; i < 3;i++)		//20,19,18,
	{
		Din_OFF;
		Delay_US(2);
		Clock_ON;
		Delay_US(2);
		Din_OFF;
		Clock_OFF;
	}
	for(i = 0; i <9; i++)		//位选
	{
		temp = data&0x01; 
		if(temp == 0) 
		{
			Din_OFF;
		}
		else
		{
			Din_ON;
		}
		data = data >> 1;
		Delay_US(2);
		Clock_ON;
		Delay_US(2);
		Din_OFF;
		Clock_OFF;
		Delay_US(2);
	}
	for(i = 0; i <8; i++)
	{
		temp = num&0x01;
		if(temp == 0)
		{
			Din_OFF;
		}
		else
		{
			Din_ON;
		}
		num = num >>1;
		Delay_US(2);
		Clock_ON;
		Delay_US(2);
		Din_OFF;
		Clock_OFF;
	}
	Blank_ON;
	Delay_US(2);
	Load_ON;
	Delay_US(2);
	Load_OFF;
	Blank_OFF;
	Delay_MS(2);
}


















