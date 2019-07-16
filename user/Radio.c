#include "Radio.h"
#define ATIIcxxDriverAddressW 0xC0
#define ATIIcxxDriverAddressR 0xC1

#define max_freq 108000     //108Mhz
#define min_freq 87500        //87.5Mhz
#define max_pll 0x339b       //108MHz??pll.
#define min_pll 0x299d        //87.5MHz??pll.
#define Add_Freq    1
#define Dec_Freq    0
#define REFERENCE_FREQ    32.768



unsigned char radio_write_data[5]={0x2d,0x56,0x20,0x11,0x00}; //?????TEA5767???(FM89.8Mhz)
unsigned char radio_read_data[5];                    
unsigned int Pll_Data;
unsigned long Frequency_Data;

void Radio_Init(void)
{
	radio_write_data[0] =0x2A;
    radio_write_data[1] =0xB6;
    radio_write_data[2] =0x41;
    radio_write_data[3] =0x11;
    radio_write_data[4] =0x40;
    ATIICxx_PWrite(&radio_write_data[0],5);//???TEA5767(89.8Mhz)
    Frequency_Data = 89800;
}
void Radio_Read(void)
{
    unsigned char temp_l,temp_h;
    Pll_Data = 0;

    ATIICxx_PRead(&radio_read_data[0],5);
   
    temp_l = radio_read_data[1];
    temp_h = radio_read_data[0];
    temp_h &= 0x3f;
    Pll_Data = temp_h*256+temp_l;
    Get_Frequency();
}

void Get_Frequency(void)
{
    unsigned char hlsi;
    unsigned int npll = 0;
   
    npll = Pll_Data;
    hlsi = radio_read_data[2]&0x10;
    if (hlsi)
        Frequency_Data = (unsigned long)((float)(npll)*(float)REFERENCE_FREQ*(float)0.25-225);    //????:KHz
    else
        Frequency_Data = (unsigned long)((float)(npll)*(float)REFERENCE_FREQ*(float)0.25+225);    //????:KHz
}

void Get_Pll(void)
{
    unsigned char hlsi;

    hlsi = radio_read_data[2]&0x10;
    if (hlsi)
        Pll_Data = (unsigned int)((float)((Frequency_Data+225)*4)/(float)REFERENCE_FREQ);    //????:k
    else
        Pll_Data = (unsigned int)((float)((Frequency_Data-225)*4)/(float)REFERENCE_FREQ);    //????:k
}

void Search(unsigned char mode)
{
    Radio_Read();
           
    if(mode)
    {
        Frequency_Data += 100;
        if(Frequency_Data > max_freq)
            Frequency_Data = min_freq;
    }
    else
    {
        Frequency_Data -= 100;
        if(Frequency_Data < min_freq)
            Frequency_Data = max_freq;
    }
             
    Get_Pll();
    radio_write_data[0] = Pll_Data/256;
    radio_write_data[1] = Pll_Data%256;
    radio_write_data[2] = 0x41;
    radio_write_data[3] = 0x11;
    radio_write_data[4] = 0x40;
    ATIICxx_PWrite(&radio_write_data[0],5);
}

void Auto_Search(unsigned char mode)
{
    Radio_Read();
    Get_Pll();
    if(mode)
    {
        radio_write_data[2] = 0xb1;
        if(Pll_Data > max_pll)
        {
            Pll_Data = min_pll;
        }
    }
    else
    {
        radio_write_data[2] = 0x41;
        if(Pll_Data < min_pll)
        {
            Pll_Data = max_pll;
        }
    }
         
    radio_write_data[0] = Pll_Data/256+0x40;
    radio_write_data[1] = Pll_Data%256;   
    radio_write_data[3] = 0x11;
    radio_write_data[4] = 0x40;
    ATIICxx_PWrite(&radio_write_data[0],5);
    Radio_Read();
    while(!(radio_read_data[0]&0x80))     //RF??????
    {
        Radio_Read();
    }   
}


void I2C_START(void)
{
	SDA_H;
	Delay_US(2);
	SCL_H;
	Delay_US(5);
	SDA_L;
	Delay_US(5);
	SCL_L;
	Delay_US(5);	
}

void I2C_STOP(void)
{
	SCL_L;
	SDA_L;
	Delay_US(2);
	SCL_H;
	Delay_US(5);
	SDA_H;
}

unsigned char I2C_WAITACK(void)
{
	unsigned char i = 20;
	SCL_L;
	Delay_US(2);
	SDA_H;
	Delay_US(2);
	SCL_H;
	do{
	i--;
	}
	while(!i);
	if(SDA_READ)
	{
		SCL_L;
		return 0;
	}
		SCL_L;
		return 1;
}
void I2C_ACK(void)
{
	SCL_L;
	SDA_L;
	Delay_US(5);
	SCL_H;
	Delay_US(5);
	SCL_L;
}
void I2C_NOACK(void)
{
	SCL_L;
	SDA_H;
	Delay_US(2);
	SCL_H;
	Delay_US(2);
	SCL_L;
}

void I2C_SENDBYTE(unsigned char byte)
{
	unsigned char i = 8;
	while(i--)
	{
		SCL_L;
		Delay_US(2);
		if(byte&0x80)
			SDA_H;
		else
			SDA_L;
		Delay_US(2);
		SCL_H;
		Delay_US(2);
		byte <<= 1;
	}
	I2C_WAITACK();
}

static unsigned char I2C_RECEIVE_BYTE(void)
{
	unsigned char i = 8, data_buffer;
	SDA_H;
	while(i--)
	{
		SCL_L;
		Delay_US(2);
		SCL_H;
		data_buffer <<=1;
		if(SDA_READ)
			data_buffer++;
	}
	return(data_buffer);
}

void ATIICxx_PWrite(unsigned char *McuAddress,unsigned char count)
{
	I2C_START();
	I2C_SENDBYTE( ATIIcxxDriverAddressW );
	while(count--)
	{
		 I2C_SENDBYTE( *(unsigned char*)McuAddress );
		 McuAddress++;
	}
	I2C_STOP();
}

void ATIICxx_PRead(unsigned char *McuAddress,unsigned char count)
{
	I2C_START();
	I2C_SENDBYTE( ATIIcxxDriverAddressR );
	while(count--)
	{
		 *McuAddress = I2C_RECEIVE_BYTE();
		 I2C_ACK();
		 McuAddress++;
	}

	I2C_NOACK();
	I2C_STOP();
}




