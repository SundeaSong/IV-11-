/******************** (C) COPYRIGHT 2013 STMicroelectronics ********************
* File Name          : main.c
* Author             :
* Version            : V1.0.0
* Date               : 01/09/2014
* Description        :
* Date               : 2017/3/27创建


                      X1 : 安全光栅                   Y1 : 气缸
                      X2 : START
                      X3 : 复位
                      X4 : 气缸原点Sensor
                      X5 : 气缸动点Sensor
                      X8 : START

*******************************************************************************/
#include "Config.h"
#include "IAD_CAL.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
/* __GNUC__ */

const unsigned char  Ascill_16[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

unsigned short int ERROR_FLAG;
unsigned short int ERROR_CODE;
const unsigned short int FW_VERSION = 15;


unsigned int  HOT_timeout, B2B_timeout, Reset_timeout;
unsigned char Start_Flag;
unsigned int Program_Cycle_Nums = 0;

unsigned int U1ProtocolAnalysis(void);
void PrintCommandsList(void);


/*******************************************************************************
* Function Name  : Main()
* Description    :
* Parameter
* Return
********************************************************************************/
int main(void)
{
    /**********************************************************************************/
    BSP_Init();                                     //Board Init，板级初始化
    OutputControl(0x0000);
    PWR_ON;
    Delay_MS(1000);

    while (1)
    {
        Tester_Control();                           //按钮控制
        U1ProtocolAnalysis();                       //命令控制
    }
}

/*******************************************************************************
* Function Name  : 串口1上位机协议解析
* Description    :
* Parameter
* Return
********************************************************************************/

unsigned int U1ProtocolAnalysis(void)
{
    unsigned char i;
    unsigned char rlen;
    unsigned char Push_flag = 0;
    unsigned char H_flag = 0;
    unsigned char R_flag = 0;
    unsigned char F_flag = 0;
    char Rx1_String[128] = {0};

    if (USARTStructure1.RX_Flag == 1)                                               //查询到有接受数据
    {
        USARTStructure1.RX_Flag = 0;                                                        //清标志位

        for (i = 0; i < USARTStructure1.RX_Len; i++)
        {
            Rx1_String[i] = toupper(USARTStructure1.RX_BUFF[i]); //全部转换大写
        }

        Rx1_String[i] = '\0';
        rlen = Get_Strlen(&Rx1_String[0]);

        if (rlen != 0)
        {
            switch (Rx1_String[0])
            {
                case 'P':
                    if (strcmp("PUSH IN", Rx1_String) == 0)                 //气缸动作
                    {
                        PUSH_CONNECT();
                        Push_flag = 1;
                    }

                    if (strcmp("PUSH OUT", Rx1_String) == 0)            //气缸复位
                    {
                        PUSH_DISCONNECT();
                        Push_flag = 1;
                    }

                    if (Push_flag == 0)
                    {
                        printf("Command Error\r\n");

                    }

                    break;

                case 'R':
                    if (strcmp("RESET", Rx1_String) == 0)               //机台复位
                    {
                        Reset_Test();
                        R_flag = 1;
                    }

                    if (strcmp("READ FIXTUREID", Rx1_String) == 0)      //读取治具ID
                    {
                        printf("FixtureID : %05d\n", Read_FixtureID());
                        R_flag = 1;
                    }

                    if (R_flag == 0)
                    {
                        printf("Command Error\r\n");
                    }

                    break;

                case 'F':
                    if (strcmp("FIRMWARE VERSION", Rx1_String) == 0)    //获取固件版本
                    {
                        Firmware();
                        F_flag = 1;
                    }

                    if (strncmp("FIXTUREID_", Rx1_String, 10) == 0)     //写治具ID
                    {
                        Write_FixtureID(&Rx1_String[10]);
                        printf("FixtureID : %05d\n", Read_FixtureID());
                        F_flag = 1;
                    }

                    if (F_flag == 0)
                    {
                        printf("Command Error\r\n");
                    }

                    break;

                case 'H':
                    if (strcmp("HARDWARE VERSION", Rx1_String) == 0)    //获取控制板版本
                    {
                        ControlBoard();
                        H_flag = 1;
                    }

                    if (strcmp("HELP", Rx1_String) == 0)                //获取帮助
                    {
                        Help_Cmd();
                        H_flag = 1;
                    }

                    if (H_flag == 0)
                    {
                        printf("Command Error\r\n");
                    }

                    break;

                default :
                    printf("Command Error\r\n");
                    break;
            }
        }
    }

    return 0;
}



