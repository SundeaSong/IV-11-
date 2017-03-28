#include "usb_hid.h"

__IO uint8_t PrevXferComplete = 1;

uint8 Send_Buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};  


/*******************************************************************************
* Function Name  :向PC发送键值
* Description    : 
* Parameter		 
* Return		 
********************************************************************************/
void SendKeyValue(unsigned char fun,unsigned char val)
{
	unsigned char i=0;
	
    if (bDeviceState == CONFIGURED)
    {
        if(PrevXferComplete)
        {			
            /* Reset the control token to inform upper layer that a transfer is ongoing */
            PrevXferComplete = 0;

            Send_Buffer[0]=fun;//function
            Send_Buffer[1]=0x00;//Reserve 
            Send_Buffer[2]=val;//key1
            Send_Buffer[3]=0x00;//key2
            Send_Buffer[4]=0x00;//key3
            Send_Buffer[5]=0x00;//key4
            Send_Buffer[6]=0x00;//key5
            Send_Buffer[7]=0x00;//key6
            //第一字节表示特殊按键，第二字节保留，后面的六字节为普通按键
            // 只有左ctrl键按下，则返回01 00 00 00 00 00 00 00
            // 然后全部按键释放，则返回00 00 00 00 00 00 00 00
            /* Copy mouse position info in ENDP1 Tx Packet Memory Area*/
            USB_SIL_Write(EP1_IN, Send_Buffer, 8);
            /* Enable endpoint for transmission */
            SetEPTxValid(ENDP1);
            while(!PrevXferComplete)
            {
                i++;
                Delay_MS(2);
                if(i>5) 
                {
                    PrevXferComplete = 1;
                    break;
                }
            }
        }			
    }
}

	

