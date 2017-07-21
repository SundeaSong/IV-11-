/******************** (C) COPYRIGHT 2013 STMicroelectronics ********************
* File Name          : main.c
* Author             :
* Version            : V0.0.2
* Date               : 01/09/2014
* Description        :
* Date                           : 2017/03/27创建
		
		动作流程：①hold锁紧---②滑台汽缸推进--->③底层汽缸动作--->④顶层汽缸左右移动--->测试完成，治具复位

		 X1:PUSH IN							Y1:PUSH
		 X2:PUSH OUT						Y2:LOCK
		 X3:LOCK ON							Y3:PULL
		 X4:LOCK OFF						Y4:TOGGLE SWITCH
		 X5:PULL ON
		 X6:PULL OFF
		 X7:TOGGLE LEFT(拨动开关)
		 X8:TOGGLE RIGHT
		 
		 X19:LOCK_BUTTON
		 X20:START_BUTTON
		 X21:RESET_BUTTON
		 X22:RASTER	(光幕)
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
const unsigned short int FW_VERSION = 1;

unsigned char Start_Flag;
unsigned char Stop_Flag;
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
    Start_Flag = 0;
    Stop_Flag  = 0;

    while (1)
    {
        Tester_Control();
        U1ProtocolAnalysis();
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
    char Rx1_String[128] = {0};

    if (USARTStructure1.RX_Flag == 1)                                               //查询到有接受数据
    {
        USARTStructure1.RX_Flag = 0;                                                        //清标志位

        for (i = 0; i < USARTStructure1.RX_Len; i++)
        {
            Rx1_String[i] = toupper(USARTStructure1.RX_BUFF[i]); //全部转换大写
        }

        Rx1_String[i] = '\0';

        switch (Rx1_String[0])
        {
            case 'L':
                if (StringCompare2("LOCK_ON", &Rx1_String[0]) == 0)
                {
												LOCK_ON();
                }

                if (StringCompare2("LOCK_OFF", &Rx1_String[0]) == 0)
                {
												LOCK_OFF();
                }
              break;
            
						case 'P':
                if (StringCompare2("PUSH_IN", &Rx1_String[0]) == 0)
                {
												PUSH_IN();
                }
								if (StringCompare2("PUSH_OUT", &Rx1_String[0]) == 0)
                {
												PUSH_OUT();
                }
								if (StringCompare2("PULL_IN", &Rx1_String[0]) == 0)
                {
										if((X1 == ON)&&(X22 == ON))
										{
											PULL_ON();
										}
								}
								if (StringCompare2("PULL_OUT", &Rx1_String[0]) == 0)
                {
										if((X1 == ON)&&(X22 == ON))
										{
											PULL_OFF();
										}
								}
                break;
						case 'T':
                if (StringCompare2("TOGGLE_LIFE", &Rx1_String[0]) == 0)
                {
									if((X5 == ON)&&(X22 == ON))
									{
											TOGGLE_LIFE();
									}
								}
								if (StringCompare2("TOGGLE_RIGHT", &Rx1_String[0]) == 0)
                {
									if((X5 == ON)&&(X22 == ON))
									{
											TOGGLE_RIGHT();
									}
								}
								break;
						case 'R':
                if (StringCompare2("RESET", &Rx1_String[0]) == 0)
                {
                    Reset_Test();
                }
								break;
            case 'H':
                if (StringCompare2("HELP", &Rx1_String[0]) == 0)
                {
                    PrintCommandsList();
                }
								break;
            case '$':
                rlen = Get_Strlen(&Rx1_String[0]);

                if (rlen == 19)
                {
                    if (StringCompare3("$C.W_TESTERID_", &Rx1_String[0], 14) == 0)
                    {
                        Write_FixtureID(&Rx1_String[14]);
                        printf("TEST_ID,%05d>\r", Read_FixtureID());
                    }
                    else
                    {
                        //ERR = 1001 ,输入格式错误
												printf("Error Command");
                        printf("TEST_ID,%05d>\r", Read_FixtureID());
                    }
                }

                if (StringCompare2("$C.GET_TESTERID", &Rx1_String[0]) == 0)
                {
                    printf("$M.TESTID,%05d>\r", Read_FixtureID());
                }

                break;

            default:
                printf("ERROR_COMMAND>\r");
                break;
        }
    }

    return 0;
}


/*******************************************************************************
* Function Name  :打印治具命令列表
* Description    : 
* Parameter		 
* Return		 
********************************************************************************/
void PrintCommandsList(void)
{
    printf("\n\\**********************Help********************\\\r\n");
		printf("LOCK_ON\r\n");
		printf("LOCK_OFF\r\n\r\n");
    printf("PUSH_IN\r\n");
    printf("PUSH_OUT\r\n\r\n");
		printf("PULL_IN\r\n");
		printf("PULL_OUT\r\n\r\n");
		printf("TOGGLE_LIFE\r\n");
		printf("TOGGLE_RIGHT\r\n\r\n");
    printf("RESET\r\nFixture rester\r\n");
		printf("$C.GET_TESTERID\r\nRead ID\r\n");
}



