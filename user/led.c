#include "led.h"

extern const unsigned int LED_Line_Ctrl[21];
extern const unsigned int LED_Point_Ctrl[21];
extern unsigned int get_ad(unsigned char charge);

unsigned char old_temp = 0;
/*--------------LED DISPLAY LINE--------------*/
void	led_display_line(unsigned char volt)
{
	unsigned char i = 0;
//	unsigned char temp = 0;
//	temp = get_ad(volt);//get ad temp

	for(i = 0; i < volt; i++)
	{
		Line_A_Control(LED_Line_Ctrl[i]);
	}
}

/*-------------LED DISPLAY POINT-------------*/
void led_display_point(unsigned char volt)
{
	unsigned char i = 0;
//	unsigned char temp = 0;
//	temp = get_ad(volt);
	for(i = 0; i < volt; i++)
	{
		Line_A_Control(LED_Point_Ctrl[i]);
//		Line_B_Control(LED_Point_Ctrl[i]);
		Delay_MS(10);
	}
}

/*------------volt and led display conversion--------------*/
unsigned char conversion_volt(void)
{
	unsigned int volt = 0;
	unsigned char volt_temp = 0;
	volt_temp = (GetVolt(ADCPrimevalValue[1]));//number 1 charge volt
	if( 0 < volt_temp <= 10)
	{
		volt = 0;
	}
	else if(10 < volt_temp <= 20)
	{
		volt = 1;
	}
	else if(20 < volt_temp <= 30)
	{
		volt = 2;
	}
	else if(30 < volt_temp <= 40)
	{
		volt = 3;
	}
	else if(40 < volt_temp <= 50)
	{
		volt = 4;
	}
	else if(50 < volt_temp <= 60)
	{
		volt = 5;
	}
	else if(60 < volt_temp <= 70)
	{
		volt = 6;
	}
	else if(70 < volt_temp <= 80)
	{
		volt = 7;
	}
	else if(80 < volt_temp <= 90)
	{
		volt = 8;
	}
	else if(90 < volt_temp <= 100)
	{
		volt = 9;
	}
	else if(100 < volt_temp <= 110)
	{
		volt = 10;
	}
	else if(110 < volt_temp <= 120)
	{
		volt = 11;
	}
	else if(120 < volt_temp <= 130)
	{
		volt = 12;
	}
	else if(130 < volt_temp <= 140)
	{
		volt = 13;
	}
	else if(140 < volt_temp <= 150)
	{
		volt = 14;
	}
	else if(150 < volt_temp <= 160)
	{
		volt = 15;
	}
	else if(160 < volt_temp <= 170)
	{
		volt = 16;
	}
	else if(170 < volt_temp <= 180)
	{
		volt = 17;
	}
	else if(180 < volt_temp <= 190)
	{
		volt = 18;
	}
	else if(190 < volt_temp <= 200)
	{
		volt = 19;
	}
	else if(20 < volt_temp )
	{
		volt = 20;
	}
	else 
	{
		volt = 0;
	}
	return volt;
}











