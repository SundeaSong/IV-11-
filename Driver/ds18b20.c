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
uint8_t serial_3[8]={0x28,0x00,0x49,0x1b,0x03,0x00,0x00,0x4c};  //���кţ���Ҫ�����Լ���DS18B20�޸ģ������ȡ������������һƪ���ܡ�

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

static void DS18B20_Mode_IPU(void)  //ʹDS18B20-DATA���ű�Ϊ����ģʽ
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}

static void DS18B20_Mode_Out_PP(void)  //ʹDS18B20-DATA���ű�Ϊ���ģʽ
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = DS18B20_PIN;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
}

static void DS18B20_Rst(void)  //�������ӻ����͸�λ����
{
  DS18B20_Mode_Out_PP();
  DS18B20_DATA_OUT(LOW);
  delay_us(750);  //�������ٲ���480us�ĵ͵�ƽ��λ�ź�
  DS18B20_DATA_OUT(HIGH);  //�����ڲ�����λ�źź��轫��������
  delay_us(15);   //�ӻ����յ������ĸ�λ�źź󣬻���15~60us���������һ����������
}

static uint8_t DS18B20_Presence(void)  //���ӻ����������صĴ�������
{
  uint8_t pulse_time = 0;

  DS18B20_Mode_IPU(); //��������Ϊ��������

//�ȴ���������ĵ�������������Ϊһ��60~240us�ĵ͵�ƽ�ź� 
//�����������û����������ʱ�����ӻ����յ������ĸ�λ�źź󣬻���15~60us���������һ����������

  while( DS18B20_DATA_IN() && pulse_time<100 )
  {
    pulse_time++;
    delay_us(1);
  }
  if( pulse_time >=100 )   //����100us�󣬴������嶼��û�е���
        return 1;
  else
        pulse_time = 0;
  while( !DS18B20_DATA_IN() && pulse_time<240 )  //�������嵽�����Ҵ��ڵ�ʱ�䲻�ܳ���240us 
  {
    pulse_time++;
    delay_us(1);
  }
  if( pulse_time >=240 )
    return 1;
  else
    return 0;
}

static uint8_t DS18B20_Read_Bit(void)  //��DS18B20��ȡһ��bit
{
  uint8_t dat;

  DS18B20_Mode_Out_PP();  //��0�Ͷ�1��ʱ������Ҫ����60us
  DS18B20_DATA_OUT(LOW);  //��ʱ�����ʼ���������������� >1us <15us �ĵ͵�ƽ�ź�
  delay_us(10);
  DS18B20_Mode_IPU(); //���ó����룬�ͷ����ߣ����ⲿ�������轫��������
  if( DS18B20_DATA_IN() == SET )
      dat = 1;
  else
     dat = 0;
  delay_us(45);   //�����ʱ������ο�ʱ��ͼ

  return dat;
}

uint8_t DS18B20_Read_Byte(void)  //��DS18B20��һ���ֽڣ���λ����
{
  uint8_t i, j, dat = 0;

  for(i=0; i<8; i++) 
  {
		j = DS18B20_Read_Bit();
		dat = (dat) | (j<<i);  
  }
  return dat;
}

void DS18B20_Write_Byte(uint8_t dat)  //дһ���ֽڵ�DS18B20����λ����
{
  uint8_t i, testb;

  DS18B20_Mode_Out_PP();
  for( i=0; i<8; i++ )
  {
    testb = dat&0x01;
    dat = dat>>1;
    if (testb) //д0��д1��ʱ������Ҫ����60us
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
  DS18B20_Write_Byte(0XCC); //���� ROM  
  DS18B20_Write_Byte(0X44); //��ʼת�� 
}

uint8_t DS18B20_Init(void)
{
  DS18B20_GPIO_Config();
  DS18B20_Rst();

  return DS18B20_Presence();
}

void DS18B20_Match_Serial(uint8_t a)    //ƥ�����к�
{
  uint8_t i;
  DS18B20_Rst();
  DS18B20_Presence();
  DS18B20_Write_Byte(0X55); //ƥ�����к�ָ��
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


//�洢���¶���16 λ�Ĵ�������չ�Ķ����Ʋ�����ʽ
//��������12λ�ֱ���ʱ������5������λ��7������λ��4��С��λ

//         |---------����----------|-----С�� �ֱ��� 1/(2^4)=0.0625----|
//���ֽ�  | 2^3 | 2^2 | 2^1 | 2^0 | 2^(-1) | 2^(-2) | 2^(-3) | 2^(-4) |

//        |-----����λ��0->��  1->��-------|-----------����-----------|
//���ֽ�  |  s  |  s  |  s  |  s  |    s   |   2^6  |   2^5  |   2^4  |
//�¶� = ����λ + ���� + С��*0.0625

float DS18B20_Get_Temp(void)
{
	u16 TempMsb = 0;
	u16 TempLsb = 0;
	u16 Temp = 0;
	float t = 0;
	DS18B20_Rst();			//��λ
	DS18B20_Presence();		//���Ӧ���ź�
	DS18B20_Write_Byte(0xcc);	//����ROM
	DS18B20_Write_Byte(0x44);	//��ʼ�¶�ת��
	
	DS18B20_Rst();					//��λ
	DS18B20_Presence();				//���Ӧ���ź�
	DS18B20_Write_Byte(0xcc);		//����ROM
	DS18B20_Write_Byte(0xbe);		//��ȡ�ݴ����������������
	DS18B20_Mode_IPU();				//���ö˿�Ϊ����ģʽ
	TempLsb = DS18B20_Read_Byte();	//��ȡ��8λ����
	TempMsb = DS18B20_Read_Byte();	//��ȡ��8λ����
	TempMsb <<= 8;					//�߰�λ��������8λ
	Temp = TempMsb|TempLsb;			//������ӣ��ó���ֵ
	t = (float)Temp*0.0625;
	printf("%4f",t);
	return t;
}


void read_serial(uint8_t *serial)  //��ȡ���к�
{
  uint8_t i;
  DS18B20_Rst();
  DS18B20_Presence();
  DS18B20_Write_Byte(0X33); //��ȡ���к�ָ��
  for(i=0;i<8;i++)
     serial[i] = DS18B20_Read_Byte(); 
}












