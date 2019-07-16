#include "ESP8266.h"

char ESP_RX_BUFF[128] = {0};
char ESP_RX_LEN = 0;
u8 ESP_PortAnalysis(char *buff)
{
	if(USARTStructure2.RX_Flag == 1)
	{
		USARTStructure2.RX_Flag = 0;
		if(StringCompare2(buff, &ESP_RX_BUFF[0]) == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
		
	}
	else
	{
		return 1;
	}
}

void ESP_RST(void)
{
	u32 i = 0;
	USART2_SendString("AT+RST\r\n",8);
	do
	{
		i++;
		Delay_MS(100);
		if(i > 50)
		{
			printf("ESP_RST_TimeOut\r\n");
			break;
		}
	}
	while(!USARTStructure2.RX_Flag);
//	printf("RX_Flag =%d\r\n",USARTStructure2.RX_Flag);
//	i = ESP_PortAnalysis("NG");
//	printf("ESP_Rev_Status = %d\r\n",i);
	if(ESP_PortAnalysis("OK") == 0)
	{
		printf("ESP_RST_OK\r\n");
	}
	else
	{
		printf("ESP_RST_Fail\r\n");
		printf("ESP_Rev_Command:\t%s\r\n",ESP_RX_BUFF);
	}
	Delay_MS(5000);
}

//wifi应用模式
//	mode	1		2		3
//	应用	从机	主机	主+从
//
void ESP_AppMode(u8 *mode)
{
	u32 i = 0;
	USART2_SendString("AT+CWMODE=",10);
	USART2_SendString(mode,8);
	do
	{
		i++;
		Delay_MS(100);
		if(i > 50)
		{
			printf("ESP_AppMode_TimeOut\r\n");
			break;
		}
	}
	while(!USARTStructure2.RX_Flag);
//	printf("\r\nDEBUG:USART1_PRINTF:%s\r\n\r\n",ESP_RX_BUFF);
	if(ESP_PortAnalysis("OK") == 0)
	{
		printf("ESP_AppMode_Set_OK\r\n");
	}
	else
	{
		printf("ESP_AppMode_Set_Fail\r\n");
		printf("ESP_Rev_Command:\t%s\r\n",ESP_RX_BUFF);
	}
}

//加入热点
//	user		password
//	用户名		密码
//	注:账户名及密码需要用双引号括起来
void ESP_Connect_AP(u8 *user,u8 *password)
{
	u32 i=0;
	USART2_SendString("AT+CWJAP=",9);
	USART2_SendString(user,strlen(user));
	USART2_SendString(",",1);
	USART2_SendString(password,strlen(password));
	USART2_SendString("\r\n",2);
//	printf("\r\nDEBUG:USART2 Send Data:%s\t%s\r\n\r\n",user,password);
//	USART1_SendString(user,strlen(user));
//	USART1_SendString(",",1);
//	USART1_SendString(password,strlen(password));
//	USART1_SendString("\r\n",2);
//	printf("\tuserlen:%d",strlen(user));
//	printf("\tpasswordlen:%d",strlen(password));
//	USART1_SendString("\r\n",2);
	
	do
	{
		i++;
		Delay_MS(100);
		if(i > 50)
		{
			printf("ESP_Connect_AP_TimeOut\r\n"); break;
		}
	}
	while(!USARTStructure2.RX_Flag);
	if(ESP_PortAnalysis("WIFI DISCONNECT") == 0)
	{
		printf("ESP_Connect_AP_OK\r\n");
	}
	else
	{
		printf("ESP_Connect_AP_Fail\r\n");
		printf("ESP_Rev_Command:\t%s\r\n",ESP_RX_BUFF);
	}
}

//退出wifi的连接
//
void ESP_Dis_Connect_AP(void)
{
	u32 i=0;
	USART2_SendString("AT+CWQAP\r\n",9);
	do
	{
		i++;
		Delay_MS(100);
		if(i > 20)
		{
			printf("ESP_Dis_Connect_AP_TimeOut\r\n");
			break;
		}
	}
	while(!USARTStructure2.RX_Flag);
	if(ESP_PortAnalysis("OK") == 0)
	{
		printf("ESP_Dis_Connect_AP_OK\r\n");
	}
	else
	{
		printf("ESP_Dis_Connect_AP_Fail\r\n");
		printf("ESP_Rev_Command:\t%s\r\n",ESP_RX_BUFF);
	}
}

//	设置连接模式
//	mode	0		1
//	模式	单路	多路
void ESP_Set_CIPMUX(u8 *mode)
{
	u32 i = 0;
	USART2_SendString("AT+CIPMUX=",10);
	USART2_SendString(mode,1);
	USART2_SendString("\r\n",2);
	do
	{
		i++;
		Delay_MS(100);
		if(i > 20)
		{
			printf("ESP_Set_CIPMUX_TimeOut\r\n");
			break;
		}
	}
	while(!USARTStructure2.RX_Flag);
	if(ESP_PortAnalysis("OK") == 0)
	{
		printf("ESP_Set_CIPMUX_OK\r\n");
	}
	else
	{
		printf("ESP_Set_CIPMUX_Fail\r\n");
		printf("ESP_Rev_Command:\t%s\r\n",ESP_RX_BUFF);
	}
}

//设置连接协议，及连接的地址
//	analysis	协议选择		UDP		TCP	
//	adderss		网址
void ESP_CIPSTART(u8 *analysis, u8 *address)
{
	u32 i = 0;
	USART2_SendString("AT+CIPSTART=",12);
	USART2_SendString(analysis,strlen(analysis));
	USART2_SendString(",",1);
	USART2_SendString(address,strlen(address));
	USART2_SendString(",123\r\n",6);
//	printf("\r\nDEBUG:USART2 Send Data:%s\t%s\r\n\r\n",analysis,address);
	USART1_SendString("DEBUG:AT+CIPSTART=",18);
	USART1_SendString(analysis,strlen(analysis));
	USART1_SendString(",",1);
	USART1_SendString(address,strlen(address));
	USART1_SendString(",123\r\n",6);
	do
	{
		i++;
		if(i > 5000)
		{
			printf("ESP_Set_CIPSTART_TimeOut\r\n");
			break;
		}
	}
	while(!USARTStructure2.RX_Flag);
	if(ESP_PortAnalysis("OK") == 0)
	{
		printf("ESP_Set_CIPSTART_OK\r\n");
	}
	else if(ESP_PortAnalysis("ALREADY CONNECTED") == 0)
	{
		printf("CIPSTART CONNECT\r\n");
	}
	else
	{
		printf("ESP_CIPSTART_Fail\r\n");
		printf("ESP_Rev_Command:\t%s\r\n",ESP_RX_BUFF);
	}
}

//设置发送字节的长度
// len 		长度设置
void ESP_Send_Len(u8 *len)
{
	u32 i = 0;
	USART2_SendString("AT+CIPSEND=",11);
	USART2_SendString(len,2);
	USART2_SendString("\r\n",2);
	do
	{
		i++;
		Delay_MS(100);
		if(i > 50)
		{
			printf("ESP_Set_CIPSEND_TimeOut\r\n");
			break;
		}
	}
	while(!USARTStructure2.RX_Flag);
	if(ESP_PortAnalysis("OK") == 0)
	{
		printf("ESP_Set_CIPSEND_OK\r\n");
	}
	else
	{
		printf("ESP_Set_CIPSEND_Fail\r\n");
		printf("ESP_Rev_Command:\t%s\r\n",ESP_RX_BUFF);
	}
}
























































