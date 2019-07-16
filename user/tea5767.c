/***************************************************************************************************
TEA5767??I2C????,????AT89S52.??11.0592Mhz?????LED???
TEA5767??I2C????.TEA5767??????5???,??PLL??14?. Fosc =11.0592Mhz.
****************************************************************************************************/
#include "regx52.h"
#include "intrins.h"
/***********************************************************************************/
#define max_freq 108000     //108Mhz
#define min_freq 87500        //87.5Mhz
#define max_pll 0x339b       //108MHz??pll.
#define min_pll 0x299d        //87.5MHz??pll.
#define Add_Freq    1
#define Dec_Freq    0
#define REFERENCE_FREQ    32.768
#define ATIIcxxDriverAddressW 0xC0
#define ATIIcxxDriverAddressR 0xC1
#define _Nop() _nop_(),_nop_(),_nop_(),_nop_(),_nop_()    /*?????*/
#define     LED     P0
void Initialization(void);
void Get_Pll(void);
void Get_Frequency(void);
void Search(unsigned char mode);
void Auto_Search(unsigned char mode);
unsigned char GetKey();
void Delay(unsigned char Time);
void Led_Display(unsigned long i);
void DelayD(unsigned char Time);
unsigned char GetKey();
void Delay(unsigned char Time);
void ATIICxx_PWrite(unsigned char *McuAddress,unsigned char count);
void ATIICxx_PRead(unsigned char *McuAddress,unsigned char count);
void I2C_Send_Byte(unsigned char sendbyte);
unsigned char I2C_Receive_Byte(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_Noack(void);

/*********************************************************************/
/* IIC????????*/
sbit I2C_SCK=P3^0; /*????????? */
sbit I2C_SDA=P3^1; /*????????? */
sbit k1=P1^7;
sbit k2=P1^6;
sbit k3=P1^5;
sbit k4=P1^4;
/*********************************************************************/
/************************************************************************/
sbit ge=P2^3;
sbit shi=P2^2;
sbit bai=P2^1;
sbit qan=P2^0;
unsigned char tab[]={ 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//??
                         //0,    1,   2   3    4    5    6    7    8    9
/************************************************************************/
unsigned char radio_write_data[5]={0x2d,0x56,0x20,0x11,0x00}; //?????TEA5767???(FM89.8Mhz)
unsigned char radio_read_data[5];                    
unsigned int Pll_Data;
unsigned long Frequency_Data;
/***********************************************************************************/
void Initialization(void)
{
    TMOD = 0x11;
    TH0 = 0x5d;
    TL0 = 0x3d;
    TR0 = 0;    //25ms
    TH1 = 0x5d;
    TL1 = 0x3d;
    TR1 = 0;    //25ms
    T2CON = 0x30;
    T2MOD = 0x00;
    RCAP2H = 0xFE;
    TH2 = RCAP2H;
    RCAP2L = 0xFB;
    TL2 = RCAP2L;
    TR2 = 0;    //2400bps
    PCON = 0x00;
    SCON = 0xD0;
    IP = 0x14;
    EX0 = 1;
    IT0 = 1;
    ET0 = 1;
    EX1 = 1;
    IT1 = 1;
    ES = 0;
    EA = 0;
}

/***********************************************************************************/
//?TEA5767??,??????
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

/***********************************************************************************/
//?PLL????
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

/***********************************************************************************/
//?????PLL
void Get_Pll(void)
{
    unsigned char hlsi;

    hlsi = radio_read_data[2]&0x10;
    if (hlsi)
        Pll_Data = (unsigned int)((float)((Frequency_Data+225)*4)/(float)REFERENCE_FREQ);    //????:k
    else
        Pll_Data = (unsigned int)((float)((Frequency_Data-225)*4)/(float)REFERENCE_FREQ);    //????:k
}

/***********************************************************************************/
//??????,mode=1,+0.1MHz; mode="0:-0".1MHz ,????TEA5767????????:SM,SUD
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

/***********************************************************************************/
//????,mode=1,??????; mode="0:??????".
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

/***********************************************************************************/
void main(void)
{
//0x2d,0x56,0x20,0x11,0x00
    unsigned long temp;
    Initialization();
    radio_write_data[0] =0x2A;
    radio_write_data[1] =0xB6;
    radio_write_data[2] =0x41;
    radio_write_data[3] =0x11;
    radio_write_data[4] =0x40;
    ATIICxx_PWrite(&radio_write_data[0],5);//???TEA5767(89.8Mhz)
    Frequency_Data = 89800;

    while(1)
    { temp= Frequency_Data;
    Led_Display(Frequency_Data);

if( k1 == 0)
   { DelayD(2);
      while(k1 == 0);//?????
      Search(Add_Freq);
   }
if( k2 == 0)
   { DelayD(2);
      while(k2 == 0);//?????
    Search(Dec_Freq);
   }
if( k3 == 0)
   { DelayD(2);
      while(k3 == 0);//?????
    Auto_Search(Add_Freq);
   }
if( k4 == 0)
   { DelayD(2);
      while(k4 == 0);//?????
    Auto_Search(Dec_Freq);
   }

    }
}

/*********************************************************************/
struct bytedata_2
{
unsigned char ByteH;
unsigned char ByteL;
};

union int2byte
{
unsigned int IntData;
struct bytedata_2 ByteData;
};
/*********************************************************************/
//??I2C??,???SCL??
void I2C_Start(void)
{
I2C_SDA=1;    /*???????????*/
_Nop();
I2C_SCK=1;
_Nop();_Nop();_Nop();_Nop();_Nop();/*??????????4.7us,??*/
I2C_SDA=0;    /*??????*/
_Nop();_Nop();_Nop();_Nop();_Nop();     /* ??????????4µs*/
I2C_SCK=0;    /*??I2C??,????????? */
_Nop();_Nop();_Nop();_Nop();_Nop();/*??????????4.7us,??*/
}
//*??I2C??
void I2C_Stop(void)
{
I2C_SCK=0;
I2C_SDA=0;   /*???????????*/
_Nop();           /*???????????*/
I2C_SCK=1;   /*??????????4µs*/
_Nop();_Nop();_Nop();_Nop();_Nop();
I2C_SDA=1;   /*??I2C??????*/
}
//MCU?????(??0????)
bit I2C_WaitAck(void)
{
unsigned char ucErrTime = 200;    //???????ACK,????

I2C_SCK=0;
I2C_SDA=1;
_Nop();
I2C_SCK=1;
while(I2C_SDA)
{
       ucErrTime--;
       if (ucErrTime == 0)
       {
          I2C_Stop();
          return 0;
        }
}

I2C_SCK=0;
return 1;
}
//MCU????
void I2C_Ack(void)
{
I2C_SCK=0;
I2C_SDA=0;
_Nop();
_Nop();
_Nop();
_Nop();
_Nop();
I2C_SCK=1;
_Nop();
_Nop();
_Nop();
_Nop();
_Nop();
I2C_SCK=0;
}
//MCU???????
void I2C_Noack(void)
{
I2C_SCK=0;
I2C_SDA=1;
_Nop();
_Nop();
I2C_SCK=1;
_Nop();
_Nop();
I2C_SCK=0;
}
void I2C_Send_Byte(unsigned char sendbyte)
{
	unsigned char i = 8;
	while( i-- )
	{
		 I2C_SCK = 0;
		 _Nop(); //_Nop();
		 if ( sendbyte &0x80 ) I2C_SDA =1;
		 else I2C_SDA =0;
		 _Nop(); //_Nop();
		 I2C_SCK = 1;
		 _Nop(); //_Nop();
		 sendbyte <<= 1;
	}
	I2C_WaitAck();
}

static unsigned char I2C_Receive_Byte(void)
{
unsigned char i = 8, data_buffer;

I2C_SDA = 1;
while ( i--)
{
   I2C_SCK =0;
   _Nop();_Nop();
   I2C_SCK =1;
   _Nop();_Nop();
   data_buffer <<= 1;

   if ( I2C_SDA ) data_buffer++;
}
return (data_buffer);
}

void ATIICxx_PWrite(unsigned char *McuAddress,unsigned char count)
{
I2C_Start();
I2C_Send_Byte( ATIIcxxDriverAddressW );
while(count--)
{
   I2C_Send_Byte( *(unsigned char*)McuAddress );
   ((unsigned char*)McuAddress)++;
}
I2C_Stop();
}

void ATIICxx_PRead(unsigned char *McuAddress,unsigned char count)
{
I2C_Start();
I2C_Send_Byte( ATIIcxxDriverAddressR );
while(count--)
{
   *McuAddress = I2C_Receive_Byte();
   I2C_Ack();
   McuAddress++;
}

I2C_Noack();
I2C_Stop();
}

void DelayD(unsigned char Time)
{
        unsigned char i;
       
        while( --Time != 0)
        {
                for(i = 0; i < 125; i++); //i ?0??125,CPU?????1 ?? ?
        }
}

/************************************************************************/
void Led_Display(unsigned long i)             //????
{
LED = tab[i/100000];
qan = 0;
bai = 1;
shi = 1;
ge = 1;
DelayD(3);
LED = tab[(i%100000)/10000];
qan = 1;
bai = 0;
shi = 1;
ge = 1;
DelayD(3);
LED = tab[((i%100000)%10000)/1000]&0x7f;
qan = 1;
bai = 1;
shi = 0;
ge = 1;
DelayD(3);
LED = tab[(((i%100000)%10000)%1000)/100];
qan = 1;
bai = 1;
shi = 1;
ge = 0;
DelayD(3);
}