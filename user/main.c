/******************** (C) COPYRIGHT 2013 STMicroelectronics ********************
* File Name          : main.c
* Author             :
* Version            : V0.0.2
* Date               : 01/09/2014
* Description        :
* Date                           : 2017/03/27创建
*******************************************************************************/
#include "Config.h"
//#include "Radio.h"
//#include "hv5812.h"
#include "WS2811.h"
#include "ESP8266.h"
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
/* __GNUC__ */

const unsigned char  Ascill_16[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const unsigned short int FW_VERSION = 0002;
//	unsigned int VoltTemp = 0;
	
unsigned int Program_Cycle_Nums = 0;
	
extern unsigned long Frequency_Data;

unsigned char ID = 0;
unsigned int U1ProtocolAnalysis(void);
void PrintCommandsList(void);
unsigned int get_ad(unsigned char charge);
void Test_ID_Set(void);
void U2ProtocolAnalysis(void);
void Btn_Control(void);
void DisplayDate(void);

unsigned char Numb[] = {0xee, 0x48, 0xba, 0xda, 0x5c, 0xd6, 0xf6, 0x4a, 0xfe, 0xde, 0x01};
//							0	  1		2	  3		4	  5		6	  7		8	  9		小数点	
//unsigned int wei[]  = {0x40, 0x20, 0x01, 0x0100, 0x02, 0x10, 0x04, 0x08, 0x80};
unsigned int wei[] = {0x08, 0x04, 0x10, 0x02, 0x0100, 0x01, 0x20, 0x40, 0x80};
//					   1     2	   3	 4	    5	   6	 7	   8	 负号
unsigned int Numb_[] ={0xef, 0x49, 0xbb, 0xdb, 0x5d, 0xd7, 0xf7, 0x4b,0xff, 0xdf, 0xa6};
//						0.	  1.	2.	  3.	4.	  5.	6.	 7.   8.    9.    C
//unsigned int Char[] = {};
/*******************************************************************************
* Function Name  : Main()
* Description    :
* Parameter
* Return
********************************************************************************/
int main(void)
{
	unsigned char display_flag = 0;
	unsigned char display_count = 0;
	BSP_Init();                       //Board Init，板级初始化
//	WS_Init();
//		DS3231_Set(19,4,18,11,13,10); // 首次设置时间，设置完成后注释掉，重新下载一次程序即可掉电保存
//		printf("DS3231_Set_OK\r\n");
	Delay_MS(500);
	Delay_MS(500);
	Delay_MS(500);
	Delay_MS(500);
//	DisplayTemp();
	printf("ESP Test Star\r\n\r\n");
	printf("Testing,Pleast Waiting...\r\n\r\n");
	printf("Testing AppMode...\r\n");
	ESP_AppMode("1");										//选择连接模式
	Delay_S(5);
	printf("\r\nTesting Rst...\r\n");
	ESP_RST();											//模块复位
	Delay_S(5);
	printf("\r\nTesting Connect to Wifi...\r\n");
	ESP_Connect_AP("\"Myzy-Guest\"","\"88889999\"");	//连接到的wifi
	Delay_S(5);
	printf("\r\nTesting CIPMUX...\r\n");
	ESP_Set_CIPMUX("0");								//单路连接模式
	Delay_S(5);
	printf("\r\nTesting CIPSTART...\r\n");
	ESP_CIPSTART("\"UDP\"","\"1.cn.pool.ntp.org\"");	//连接到的地址
	Delay_S(5);
	printf("\r\nTesting Set CIPSEND...\r\n");
	ESP_Send_Len("48");									//发送字节的长度
	
	printf("\r\nESP Test End\r\n");

    while (1)
    {
//		printf("ESP Test Star\r\n");
//		ESP_RST();
//		printf("ESP Test End");
//		RGB_Disp();
//		U2ProtocolAnalysis();		//蓝牙数据解析
//		Btn_Control();				//按键控制
//		if(display_flag == 0)
//		{
//			DisplayTime();				//单独显示时间
//		}
//		else if(display_flag == 1)		//单独显示温度
//		{
//			DisplayTemp();
//		}
//		else if(display_flag == 2)		//时间及日期交替显示
//		{
//			display_count++;
//			if(display_count < 1000)
//			{
//				DisplayTime();	
//			}
//			else
//			{
//				DisplayDate();
//				if(display_count >2000)
//				{
//					display_count = 0;
//				}
//			}
//		}
//		else if(display_flag == 3)		//时间及温度交替显示
//		{
//			display_count++;
//			if(display_count < 1000)
//			{
//				DisplayTime();	
//			}
//			else
//			{
//				DisplayTemp();
//				if(display_count >2000)
//				{
//					display_count = 0;
//				}
//			}
//		}
	}
}

//蓝牙数据解析
void U2ProtocolAnalysis(void)
{
	char i;
	char year[2];
	char month[2];
	char date[2];
	char time[2];
	char minute[2];
	char second[2];
    char Bluetooth_Char[128] = {0};

	if(USARTStructure2.RX_Flag == 1)
	{
		USARTStructure2.RX_Flag =0;
		for(i = 0; i < USARTStructure2.RX_Len;i++)
		{
			Bluetooth_Char[i] = toupper(USARTStructure1.RX_BUFF[i]); //全部转换大写
		}
		Bluetooth_Char[i] = '\0';
		switch(Bluetooth_Char[0])
		{
			case 'T':
			{
				if(StringCompare2("TIME:", &Bluetooth_Char[0]) == 0)
				{
					//TIME:2019/04/22 10:13:43
					strncpy(year,Bluetooth_Char+8,2);
					strncpy(month,Bluetooth_Char+11,2);
					strncpy(date,Bluetooth_Char+14,2);
					strncpy(time,Bluetooth_Char+17,2);
					strncpy(minute,Bluetooth_Char+20,2);
					strncpy(second,Bluetooth_Char+23,2);
					
					DS3231_Set(atoi(year),atoi(month),atoi(date),atoi(time),atoi(minute),atoi(second));
				}
				break;
			}
			case 'S':
			{
				if(StringCompare2("SET_CLOCK:",&Bluetooth_Char[0]) == 0)
				{
					//SET_CLOCK:10:43
					//Handware not interrupt output
					//Use flash to simulate EEPROM
					strncpy(time,Bluetooth_Char+11,2);
					strncpy(minute,Bluetooth_Char+14,2);
				}
				if(StringCompare2("SET_CLOCK_CLOSE",&Bluetooth_Char[0]) == 0)
				{
					//Close Clock
					strncpy(time,Bluetooth_Char+11,2);
					strncpy(minute,Bluetooth_Char+14,2);
				}
				break;
			}
			case 'R':
				if(StringCompare2("READ_CLOCK",&Bluetooth_Char[0]) == 0)
				{
					
					break;
				}
			default:break;
		}
	}
}

//按键控制部分解析
void Btn_Control(void)
{
	//btn1		btn2		btn3		btn4
	//k2		k3			k4			k5
	//menu		set			down		up
	//PA8		PB15		PB14		PB13
	 int year,month,date,time,minute,second;
	u8 year1,year2,month1,month2,date1,date2,time1,time2,minute1,minute2,second1,second2;
	unsigned char SetTimeFlag = 0;
	if(key_Menu == 0)
	{
		Delay_MS(1000);
		Delay_MS(1000);
		if(key_Menu == 0)			//enter the timing function menu
		{
			get_show_time();	//Get the current time
			year = calendar.w_year;
			month = calendar.w_month;
			date = calendar.w_date;
			time =calendar.hour;
			minute = calendar.min;
			second = calendar.sec;
			year1 = calendar.w_year /10;
			year2 = calendar.w_year %10;
			month1 = calendar.w_month /10;
			month2 = calendar.w_month %10;
			date1 = calendar.w_date /10;
			date2 = calendar.w_date %10;
			
			time1 = calendar.hour /10;
			time2 = calendar.hour %10;
			minute1 = calendar.min /10;
			minute2 = calendar.min %10;
			second1 = calendar.sec /10;
			second2 = calendar.sec %10;
			//默认进入调年份的选择中
			switch(SetTimeFlag)
			{
				case 0:					//set year
					if(key_Up == 0)
					{
						while(!key_Up);		//松手检测
						year++;
						if(year > 23)
						{
							year = 0;
						}
						year1 = year/10;
						year2 = year%10;
						hv5812_data(wei[0],Numb[year1]);
						hv5812_data(wei[1],Numb[year2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[month1]);
						hv5812_data(wei[4],Numb[month2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[date1]);
						hv5812_data(wei[7],Numb[date2]);
					}
					if(key_Down == 0)
					{
						while(!key_Down);
						year--;
						if(year < 0)
						{
							year = 99;
						}
						year1 = year/10;
						year2 = year%10;
						hv5812_data(wei[0],Numb[year1]);
						hv5812_data(wei[1],Numb[year2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[month1]);
						hv5812_data(wei[4],Numb[month2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[date1]);
						hv5812_data(wei[7],Numb[date2]);
					}
					if(key_Set == 0)
					{
						while(!key_Set);
						SetTimeFlag++;
						if(SetTimeFlag > 5)
						{
							SetTimeFlag = 0;
						}
					}
					if(key_Menu == 0)
					{
						Delay_MS(1000);
						if(key_Menu == 0)
						{
							DS3231_Set(year,month,date,time,minute,second);	
							break;
						}
					}
				case 1:					//set month
					if(key_Up == 0)
					{
						while(!key_Up);		//松手检测
						month++;
						if(month > 12)
						{
							month = 0;
						}
						month1 = month/10;
						month2 = month%10;
						hv5812_data(wei[0],Numb[year1]);
						hv5812_data(wei[1],Numb[year2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[month1]);
						hv5812_data(wei[4],Numb[month2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[date1]);
						hv5812_data(wei[7],Numb[date2]);
					}
					if(key_Down == 0)
					{
						while(!key_Down);
						month--;
						if(year < 0)
						{
							year = 12;
						}
						month1 = month/10;
						month2 = month%10;
						hv5812_data(wei[0],Numb[year1]);
						hv5812_data(wei[1],Numb[year2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[month1]);
						hv5812_data(wei[4],Numb[month2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[date1]);
						hv5812_data(wei[7],Numb[date2]);
					}
					if(key_Set == 0)
					{
						while(!key_Set);
					}
					if(key_Menu == 0)
					{
						Delay_MS(1000);
						if(key_Menu == 0)
						{
							DS3231_Set(year,month,date,time,minute,second);	
							break;
						}
					}
				case 2:						//set date
					if(key_Up == 0)
					{
						while(!key_Up);		//松手检测
						date++;
						if(date > 12)
						{
							date = 0;
						}
						date1 = date/10;
						date2 = date%10;
						hv5812_data(wei[0],Numb[year1]);
						hv5812_data(wei[1],Numb[year2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[month1]);
						hv5812_data(wei[4],Numb[month2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[date1]);
						hv5812_data(wei[7],Numb[date2]);
					}
					if(key_Down == 0)
					{
						while(!key_Down);
						date--;
						if(year < 0)
						{
							year = 12;
						}
						date1 = date/10;
						date2 = date%10;
						hv5812_data(wei[0],Numb[year1]);
						hv5812_data(wei[1],Numb[year2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[month1]);
						hv5812_data(wei[4],Numb[month2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[date1]);
						hv5812_data(wei[7],Numb[date2]);
					}
					if(key_Set == 0)
					{
						while(!key_Set);
						SetTimeFlag++;
						if(SetTimeFlag > 5)
						{
							SetTimeFlag = 0;
						}
					}
					if(key_Menu == 0)
					{
						Delay_MS(1000);
						if(key_Menu == 0)
						{
							DS3231_Set(year,month,date,time,minute,second);	
							break;
						}
					}
				case 3:						//set hours
					if(key_Up == 0)
					{
						while(!key_Up);		//松手检测
						time++;
						if(time > 23)
						{
							time = 0;
						}
						time1 = time/10;
						time2 = time%10;
						hv5812_data(wei[0],Numb[time1]);
						hv5812_data(wei[1],Numb[time2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[minute1]);
						hv5812_data(wei[4],Numb[minute2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[second1]);
						hv5812_data(wei[7],Numb[second2]);
					}
					if(key_Down == 0)
					{
						while(!key_Down);
						time--;
						if(time < 0)
						{
							time = 23;
						}
						time1 = time/10;
						time2 = time%10;
						hv5812_data(wei[0],Numb[time1]);
						hv5812_data(wei[1],Numb[time2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[minute1]);
						hv5812_data(wei[4],Numb[minute2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[second1]);
						hv5812_data(wei[7],Numb[second2]);
					}
					if(key_Set == 0)
					{
						while(!key_Set);
						SetTimeFlag++;
						if(SetTimeFlag > 5)
						{
							SetTimeFlag = 0;
						}
					}
					if(key_Menu == 0)
					{
						Delay_MS(1000);
						if(key_Menu == 0)
						{
							DS3231_Set(year,month,date,time,minute,second);	
							break;
						}
					}
				case 4:						//set minute
					if(key_Up == 0)
					{
						while(!key_Up);		//松手检测
						minute++;
						if(minute > 59)
						{
							minute = 0;
						}
						minute1 = minute/10;
						minute2 = minute%10;
						hv5812_data(wei[0],Numb[time1]);
						hv5812_data(wei[1],Numb[time2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[minute1]);
						hv5812_data(wei[4],Numb[minute2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[second1]);
						hv5812_data(wei[7],Numb[second2]);
					}
					if(key_Down == 0)
					{
						while(!key_Down);
						minute--;
						if(minute < 0)
						{
							minute = 59;
						}
						minute1 = minute/10;
						minute2 = minute%10;
						hv5812_data(wei[0],Numb[time1]);
						hv5812_data(wei[1],Numb[time2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[minute1]);
						hv5812_data(wei[4],Numb[minute2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[second1]);
						hv5812_data(wei[7],Numb[second2]);
					}
					if(key_Set == 0)
					{
						while(!key_Set);
						SetTimeFlag++;
						if(SetTimeFlag > 5)
						{
							SetTimeFlag = 0;
						}
					}
					if(key_Menu == 0)
					{
						Delay_MS(1000);
						if(key_Menu == 0)
						{
							DS3231_Set(year,month,date,time,minute,second);	
							break;
						}
					}
				case 5:
					if(key_Up == 0)
					{
						while(!key_Up);		//松手检测
						second++;
						if(second > 59)
						{
							second = 0;
						}
						second1 = second/10;
						second2 = second%10;
						hv5812_data(wei[0],Numb[time1]);
						hv5812_data(wei[1],Numb[time2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[minute1]);
						hv5812_data(wei[4],Numb[minute2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[second1]);
						hv5812_data(wei[7],Numb[second2]);
					}
					if(key_Down == 0)
					{
						while(!key_Down);
						second--;
						if(second < 0)
						{
							second = 59;
						}
						second1 = second/10;
						second2 = second%10;
						hv5812_data(wei[0],Numb[time1]);
						hv5812_data(wei[1],Numb[time2]);
						hv5812_data(wei[2],0x10);
						hv5812_data(wei[3],Numb[minute1]);
						hv5812_data(wei[4],Numb[minute2]);
						hv5812_data(wei[5],0x10);
						hv5812_data(wei[6],Numb[second1]);
						hv5812_data(wei[7],Numb[second2]);
					}
					if(key_Set == 0)
					{
						while(!key_Set);
						SetTimeFlag++;
						if(SetTimeFlag > 5)
						{
							SetTimeFlag = 0;
						}
					}
					if(key_Menu == 0)
					{
						Delay_MS(1000);
						if(key_Menu == 0)
						{
							DS3231_Set(year,month,date,time,minute,second);	
							break;
						}
					}
			}
		}
	}
}

//显示时间及日期
void DisplayTime(void)
{
		hv5812_data(wei[0],Numb[shi1]);
		hv5812_data(wei[1],Numb[shi2]);
		hv5812_data(wei[2],0x10);
		hv5812_data(wei[3],Numb[fen1]);
		hv5812_data(wei[4],Numb[fen2]);
		hv5812_data(wei[5],0x10);
		hv5812_data(wei[6],Numb[miao1]);
		hv5812_data(wei[7],Numb[miao2]);
		Delay_US(5);
}

//显示日期
void DisplayDate(void)
{
		hv5812_data(wei[0],Numb[nian1]);
		hv5812_data(wei[1],Numb[nian2]);
		hv5812_data(wei[2],0x10);
		hv5812_data(wei[3],Numb[yue1]);
		hv5812_data(wei[4],Numb[yue2]);
		hv5812_data(wei[5],0x10);
		hv5812_data(wei[6],Numb[ri1]);
		hv5812_data(wei[7],Numb[ri2]);
		Delay_US(5);
}
//显示温度及湿度
void DisplayTemp(void)
{
	hv5812_data(wei[1],0x10);
	hv5812_data(wei[2],Numb[t1]);
	hv5812_data(wei[3],Numb_[t2]);
	hv5812_data(wei[4],Numb[t3]);
	hv5812_data(wei[5],Numb[t4]);
	hv5812_data(wei[6],Numb[10]);
	hv5812_data(wei[7],0x10);
}















