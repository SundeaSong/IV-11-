#include "IAD_CAL.h"
	uint8_t LockFlag = 0;

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


void Tester_Control(void)
{
    Reset_Control();
    Start_Control();
		LockBotton_Control();
}
//复位按钮
void Reset_Control(void)
{
    if (X21 == 0)
    {
			Reset_Test();
    }
}
//锁紧动作
void LockBotton_Control(void)
{
	if(X19 == 0)
	{
		LOCK_ON();
	}
}
//hoder推进推出动作
void Start_Control()
{
	if((X20 == ON)&&(X3 == ON))
	{
		PUSH_IN();
	}
}


void LOCK_ON(void)
{
	Y2_ON;
	Delay_S(2);
	if(X4 == OFF)
	{
		printf("LOCK_ON_OK\r\n");
	}
	else
	{
		printf("LOCK_ON_FAIL\r\n");
	}
}

void LOCK_OFF(void)
{
	Y2_OFF;
	Delay_S(1);
	if(X4 == ON)
	{
		printf("LOCK_OFF_OK\r\n");
	}
	else
	{
		printf("LOCK_OFF_FAIL\r\n");

	}
}

void PUSH_IN(void)
{
	Y1_ON;
	Delay_S(2);
	if(X1 == ON)
	{
		printf("PUSH_IN_OK\r\n");
	}
	else
	{
		printf("PUSH_IN_FAIL\r\n");
	}
}

void PUSH_OUT(void)
{
	Y1_OFF;
	Delay_S(2);
	if(X2 == ON)
	{
		printf("PUSH_OUT_OK\r\n");
	}
	else
	{
		printf("PUSH_OUT_FAIL\r\n");
	}
}

void PULL_ON(void)
{
	Y3_ON;
	Delay_S(2);
	if(X5 == ON)
	{
		printf("PULL_ON_OK\r\n");
	}
	else
	{
		printf("PULL_ON_FAIL\r\n");
	}
}

void PULL_OFF(void)
{
	Y3_OFF;
	Delay_S(2);
	if(X6 == ON)
	{
		printf("PULL_OFF_OK\r\n");
	}
	else
	{
		printf("PULL_OFF_FAIL\r\n");
	}
}

void TOGGLE_RIGHT(void)
{
	Y4_ON;
	Delay_S(2);
	if(X7 == ON)
	{
		printf("TOGGLE_RIGHT_OK\r\n");
	}
	else
	{
		printf("TOGGLE_RIGHT_FAIL\r\n");
	}
}

void TOGGLE_LIFE(void)
{
	Y4_OFF;
	Delay_S(2);
	if(X8 == ON)
	{
		printf("TOGGLE_LIFE_OK\r\n");
	}
	else
	{
		printf("TOGGLE_LIFE_FAIL\r\n");
	}
}

void Reset_Test(void)
{
	Y4_OFF;
	Delay_MS(500);
	Y3_OFF;
	Delay_MS(500);
	Y1_OFF;
	Delay_MS(500);
//	if(X2 == ON)
	while(X2);
	Delay_MS(500);
	Y2_OFF;
	printf("RESET_OK\r\n");
}














