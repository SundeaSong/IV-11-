#include "DS3231.h"
#include "config.h"  
     
_calendar_obj calendar;

#define DS3231_WriteAddress 0xD0   
#define DS3231_ReadAddress  0xD1

u8 BCD2HEX(u8 val)
{
    u8 i;
    i= val&0x0f;
    val >>= 4;
    val &= 0x0f;
    val *= 10;
    i += val;
    
    return i;
}

u16 B_BCD(u8 val)
{
  u8 i,j,k;
  i=val/10;
  j=val%10;
  k=j+(i<<4);
  return k;
}


void I2cByteWrite(u8 addr,u8 bytedata)
{
  TWI_Start();
  Delay_US(5);
  TWI_SendByte(DS3231_WriteAddress);
  TWI_WaitAck();
  Delay_US(5);
  TWI_SendByte(addr);
  TWI_WaitAck();
  Delay_US(5);
  TWI_SendByte(bytedata);
  TWI_WaitAck();
  Delay_US(5);
  TWI_Start();
}	


u8 I2cByteRead(u8 addr)
{
  u8 Dat=0;
  
  TWI_Start();
  TWI_SendByte(DS3231_WriteAddress);
  TWI_WaitAck();
  Delay_US(5);
  TWI_SendByte(addr);
  TWI_WaitAck();
  Delay_US(5);
  TWI_Start();
  TWI_SendByte(DS3231_ReadAddress);
  TWI_WaitAck();
  Delay_US(5);
  Dat=TWI_ReceiveByte();
  TWI_Start();
  return Dat;
} 



void DS3231_Init(void)
{
	I2C_EE_Init();
	I2cByteWrite(0x0e,0);
	Delay_MS(2); 

	
    I2cByteWrite(0x0f,0x0);
	Delay_MS(2); 
}
void DS3231_Get(void)
{
  calendar.w_year=I2cByteRead(0x06);  
  calendar.w_month=I2cByteRead(0x05);  
  calendar.w_date=I2cByteRead(0x04); 
  calendar.hour=I2cByteRead(0x02);  
  calendar.min=I2cByteRead(0x01);
  calendar.sec=I2cByteRead(0x00);
}

void DS3231_Set(u8 yea,u8 mon,u8 da,u8 hou,u8 min,u8 sec)
{
  u8 temp=0;
  
  temp=B_BCD(yea);
  I2cByteWrite(0x06,temp);
  
  temp=B_BCD(mon);
  I2cByteWrite(0x05,temp);
   
  temp=B_BCD(da);
  I2cByteWrite(0x04,temp);
  
  temp=B_BCD(hou);
  I2cByteWrite(0x02,temp);
  
  temp=B_BCD(min);
  I2cByteWrite(0x01,temp);
  
  temp=B_BCD(sec);
  I2cByteWrite(0x00,temp);
}


void get_show_time(void)
{


calendar.w_year=I2cByteRead(0x06);  
calendar.w_year=BCD2HEX(calendar.w_year);


calendar.w_month=I2cByteRead(0x05); 
calendar.w_month=BCD2HEX(calendar.w_month);


calendar.w_date=I2cByteRead(0x04);  
calendar.w_date=BCD2HEX(calendar.w_date);
 

calendar.hour=I2cByteRead(0x02); 
calendar.hour&=0x3f;                   
calendar.hour=BCD2HEX(calendar.hour);


calendar.min=I2cByteRead(0x01);
calendar.min=BCD2HEX(calendar.min);
  
  
calendar.sec=I2cByteRead(0x00);
calendar.sec=BCD2HEX(calendar.sec);
}


