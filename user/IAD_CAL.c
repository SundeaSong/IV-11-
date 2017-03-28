#include "IAD_CAL.h"
//Read Fixture ID from EEPROM
//#define NEW_TESTER

#define MAXTimes  360000        //1H

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


//��λ��ť
void Reset_Control(void)
{
    unsigned char stopflag1 = 0;

    if ((X3 == 0) && (X1 == 0))
    {
        Delay_MS(50);

        if ((X1 == 0) && (X3 == 0) && (stopflag1 == 0))
        {
            stopflag1++;
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


//������ť
void StartButton_Control(void)
{
    unsigned char flag1 = 0;
    unsigned char flag2 = 0;

    if ((X2 == 0) && (X8 == 0))
    {
        Delay_MS(50);

        if ((X2 == 0) && (X8 == 0))
        {
            flag1++;
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

//��ť��ʼ��
void Tester_Control(void)
{
    Reset_Control();
    StartButton_Control();
}

//���ư�汾
void ControlBoard(void)
{
    printf("HW : V1.0\r\n");
}

//�̼��汾
void Firmware(void)
{
    printf("FW : V1.0.0\r\n");
}

//���׶���
void PUSH_CONNECT(void)
{
    if ((X1 == 0) && (X3 == 1))
    {
        Y1_ON;

        while (X5);

        printf("OK@_@\r\n");
    }
}

//���׸�λ
void PUSH_DISCONNECT(void)
{
    if ((X1 == 0) && (X3 == 1))
    {
        Y1_OFF;

        while (X4);

        printf("0K@_@\r\n");
    }
}

//���λ
void Reset_Test(void)
{
    Delay_MS(500);
    Y1_OFF;

    while (X4);

    printf("OK@_@\r\n");
}

void Help_Cmd(void)
{
    printf("\n\\**********************Help********************\\\n");
    printf("PUSH IN                        \"Cylinder stretched out\"\n");
    printf("PUSH OUT                    \"Cylinder rester\"\n");
    printf("RESET                            \"Fixture rester\"\n");
    printf("FIXTUREID_                  \"Write fixture ID\"\n");
    printf("READ FIXTUREID         \"Read fixture ID\"\n");
    printf("FIRMWARE VERSION    \"Read the firmware version\"\n");
    printf("HARDWARE VERSION  \"Read hardware version\"\n");
}


