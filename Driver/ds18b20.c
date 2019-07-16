#include "ds18b20.h"
#include "config.h"
#define DS_R	GPIOB->IDR  & GPIO_Pin_12
#define DS_H	GPIOB->BSRR = GPIO_Pin_12
#define DS_L	GPIOB->BRR  = GPIO_Pin_12

#define DS_IN(); {GPIOB->CRH &= 0xfff0ffff;	GPIOB ->CRH |= 0x00080000;}
#define DS_OUT(); {GPIOB ->CRH &= 0xfff0ffff; GPIOB ->CRH |= 0x00030000;}
void delay_us(unsigned int nCount_temp)
{
	u32 nCount=nCount_temp*8;
	while(nCount--);
}

uint8_t serial_1[8]={0x28,0x2d,0x9a,0xdd,0x02,0x00,0x00,0x3b}; 
uint8_t serial_2[8]={0x28,0x3b,0x2b,0xbc,0x02,0x00,0x00,0x4f};
uint8_t serial_3[8]={0x28,0x00,0x49,0x1b,0x03,0x00,0x00,0x4c};  //序列号，需要根据自己的DS18B20修改，具体读取方法，会有另一篇介绍。

static void DS18B20_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(DS18B20_CLK, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);

  GPIO_SetBits(DS18B20_PORT, DS18B20_PIN);  
}

static void DS18B20_Mode_IPU(void)  //使DS18B20-DATA引脚变为输入模式
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}

static void DS18B20_Mode_Out_PP(void)  //使DS18B20-DATA引脚变为输出模式
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}

static void DS18B20_Rst(void)  //主机给从机发送复位脉冲
{
  DS18B20_Mode_Out_PP();
  DS18B20_DATA_OUT(LOW);
  delay_us(750);  //主机至少产生480us的低电平复位信号
  DS18B20_DATA_OUT(HIGH);  //主机在产生复位信号后，需将总线拉高
  delay_us(15);   //从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲
}

static uint8_t DS18B20_Presence(void)  //检测从机给主机返回的存在脉冲
{
  uint8_t pulse_time = 0;

  DS18B20_Mode_IPU(); //主机设置为上拉输入

//等待存在脉冲的到来，存在脉冲为一个60~240us的低电平信号 
//如果存在脉冲没有来则做超时处理，从机接收到主机的复位信号后，会在15~60us后给主机发一个存在脉冲

  while( DS18B20_DATA_IN() && pulse_time<100 )
  {
    pulse_time++;
    delay_us(1);
  }
  if( pulse_time >=100 )   //经过100us后，存在脉冲都还没有到来
        return 1;
  else
        pulse_time = 0;
  while( !DS18B20_DATA_IN() && pulse_time<240 )  //存在脉冲到来，且存在的时间不能超过240us 
  {
    pulse_time++;
    delay_us(1);
  }
  if( pulse_time >=240 )
    return 1;
  else
    return 0;
}

static uint8_t DS18B20_Read_Bit(void)  //从DS18B20读取一个bit
{
  uint8_t dat;

  DS18B20_Mode_Out_PP();  //读0和读1的时间至少要大于60us
  DS18B20_DATA_OUT(LOW);  //读时间的起始：必须由主机产生 >1us <15us 的低电平信号
  delay_us(10);
  DS18B20_Mode_IPU(); //设置成输入，释放总线，由外部上拉电阻将总线拉高
  if( DS18B20_DATA_IN() == SET )
      dat = 1;
  else
     dat = 0;
  delay_us(45);   //这个延时参数请参考时序图

  return dat;
}

uint8_t DS18B20_Read_Byte(void)  //从DS18B20读一个字节，低位先行
{
  uint8_t i, j, dat = 0;

  for(i=0; i<8; i++) 
  {
		j = DS18B20_Read_Bit();
		dat = (dat) | (j<<i);  
  }
  return dat;
}

void DS18B20_Write_Byte(uint8_t dat)  //写一个字节到DS18B20，低位先行
{
  uint8_t i, testb;

  DS18B20_Mode_Out_PP();
  for( i=0; i<8; i++ )
  {
    testb = dat&0x01;
    dat = dat>>1;
    if (testb) //写0和写1的时间至少要大于60us
    {
        DS18B20_DATA_OUT(LOW);
        delay_us(8);
        DS18B20_DATA_OUT(HIGH);
        delay_us(58);
    }
  else
    {
        DS18B20_DATA_OUT(LOW);
        delay_us(70);
        DS18B20_DATA_OUT(HIGH);
        delay_us(2);
      }
  }
}

void DS18B20_Start(void)
{
  DS18B20_Rst();   
  DS18B20_Presence();  
  DS18B20_Write_Byte(0XCC); //跳过 ROM  
  DS18B20_Write_Byte(0X44); //开始转换 
}

uint8_t DS18B20_Init(void)
{
  DS18B20_GPIO_Config();
  DS18B20_Rst();

  return DS18B20_Presence();
}

void DS18B20_Match_Serial(uint8_t a)    //匹配序列号
{
  uint8_t i;
  DS18B20_Rst();
  DS18B20_Presence();
  DS18B20_Write_Byte(0X55); //匹配序列号指令
  if(a==1)
  {
    for(i=0;i<8;i++)
       DS18B20_Write_Byte(serial_1[i]);
  }
  else if(a==2)
  {
    for(i=0;i<8;i++)
       DS18B20_Write_Byte(serial_2[i]);
  }
  else if(a==3)
  {
    for(i=0;i<8;i++)
       DS18B20_Write_Byte(serial_3[i]);
  }       
}


//存储的温度是16 位的带符号扩展的二进制补码形式
//当工作在12位分辨率时，其中5个符号位，7个整数位，4个小数位

//         |---------整数----------|-----小数 分辨率 1/(2^4)=0.0625----|
//低字节  | 2^3 | 2^2 | 2^1 | 2^0 | 2^(-1) | 2^(-2) | 2^(-3) | 2^(-4) |

//        |-----符号位：0->正  1->负-------|-----------整数-----------|
//高字节  |  s  |  s  |  s  |  s  |    s   |   2^6  |   2^5  |   2^4  |
//温度 = 符号位 + 整数 + 小数*0.0625

float DS18B20_Get_Temp(void)
{
	u16 TempMsb = 0;
	u16 TempLsb = 0;
	u16 Temp = 0;
	float t = 0;
	DS18B20_Rst();			//复位
	DS18B20_Presence();		//检测应答信号
	DS18B20_Write_Byte(0xcc);	//跳过ROM
	DS18B20_Write_Byte(0x44);	//开始温度转换
	
	DS18B20_Rst();					//复位
	DS18B20_Presence();				//检测应答信号
	DS18B20_Write_Byte(0xcc);		//跳过ROM
	DS18B20_Write_Byte(0xbe);		//读取暂存器里面的数据命令
	DS18B20_Mode_IPU();				//设置端口为输入模式
	TempLsb = DS18B20_Read_Byte();	//读取低8位数据
	TempMsb = DS18B20_Read_Byte();	//读取高8位数据
	TempMsb <<= 8;					//高八位数据左移8位
	Temp = TempMsb|TempLsb;			//数据相加，得出总值
	t = (float)Temp*0.0625;
	printf("%4f",t);
	return t;
}


void read_serial(uint8_t *serial)  //读取序列号
{
  uint8_t i;
  DS18B20_Rst();
  DS18B20_Presence();
  DS18B20_Write_Byte(0X33); //读取序列号指令
  for(i=0;i<8;i++)
     serial[i] = DS18B20_Read_Byte(); 
}












