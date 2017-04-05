#include "IAD_CAL.h"

char Barcode_Encoded[100] = {'\0'};

unsigned  int Read_FixtureID(void)
{
    unsigned char id[3] = {0};
    I2C_EE_BufferRead(id, FID_Address, 3);
    return (id[0] << 16) + (id[1] << 8) + id[2];
}
//Write Fixture ID to EEPROM
void Write_FixtureID(char *id)
{
    unsigned char id_temp[3] = {0};
    unsigned int fix_id = atoi(id);
    id_temp[0] = (fix_id >> 16) & 0xff;
    id_temp[1] = (fix_id >> 8) & 0xff;
    id_temp[2] = fix_id & 0xff;
    I2C_EE_BufferWrite(id_temp, FID_Address, 3);
}


//复位按钮
void Reset_Control(void)
{
    unsigned char stopflag1 = 0;

    if ((X3 == 0) && (X1 == 0))
    {
        Delay_MS(50);
        if ((X1 == 0) && (X3 == 0) && (stopflag1 == 0))
        {
            stopflag1 = 1;
        }

        if ((stopflag1 == 1) && (X1 == 0))
        {
            Delay_MS(500);
            Y1_OFF;
            while (X4 != 0) {};
            stopflag1 = 0;
        }
    }
}
//启动按钮
void StartButton_Control(void)
{
    unsigned char flag1 = 0;
    unsigned char flag2 = 0;

    if ((X2 == 0) && (X8 == 0))
    {
        Delay_MS(50);
        if ((X2 == 0) && (X8 == 0))
        {
            flag1 = 1;
        }
        while ((!X2) && (!X8));
        if ((flag1 == 1) && (X1 == 0) && (X3 == 1))
        {
            Delay_MS(500);
            Y1_ON;
            while (X5 != 0) {};
            flag1 = 0;
            flag2++;
        }

        if (flag2 == 1)
        {
            flag2 = 0;
            printf("Start\r\n");
            printf("OK@_@\r\n");
        }
    }
}

//按钮初始化
void Tester_Control(void)
{
    Reset_Control();
    StartButton_Control();
}

//气缸动作
void PUSH_CONNECT(void)
{
    if ((X1 == 0) && (X3 == 1))
    {
			Delay_MS(50);
			if((X1 == 0)&&(X3 == 1))
      {  
					Y1_ON;
			}
      while (X5);
      printf("OK@_@\r\n");
    }
}

//气缸复位
void PUSH_DISCONNECT(void)
{
    if ((X1 == 0) && (X3 == 1))
    {
			Delay_MS(50);
			if((X1 == 0)&&(X3 == 1))
			{
					Y1_OFF;
			}
      while (X4);
      printf("0K@_@\r\n");
    }
}

//命令复位
void Reset_Test(void)
{
    Delay_MS(500);
    Y1_OFF;
    while (X4);
    printf("OK@_@\r\n");
}



