#include "myiic.h"
#include "delay.h"
#include "oled.h"
//��ʼ��IIC
extern u8 OLED_GRAM[128][8];	 
void IIC_Init(void)
{					     
 	RCC->APB2ENR|=1<<4;    //��ʹ������IO PORTCʱ�� 							 
	GPIOB->CRH&=0XFFFFF00F;//PC9/10 �������
	GPIOB->CRH|=0X00000330;	   
	GPIOB->ODR|=3<<11;     //PC9,10 �����
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	
	SDA_OUT();     //sda�����
	IIC_SDA=1;	   
	IIC_SCL=1; 
	delay_us(1);//LED0 = 0;	
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(1);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(1); 
	IIC_SCL=1;//STOP:when CLK is high DATA change form low to high
 	delay_us(1); 
	IIC_SDA=1;//����I2C���߽����ź� 						   	
}
//�ȴ�Ӧ���źŵ���
//1������Ӧ��ʧ��
//0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{   
		
    u8 t;  
		SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(1);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(1); 
		IIC_SCL=0;	
		delay_us(1);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
				IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)
					receive++;   
				delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}





//��һ���ֽ�
u8 OLED_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>256)
	{
		IIC_Send_Byte(0XA0);	   
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));  	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           		   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();   
	return temp;
}
   
//дһ���ֽ�
void OLED_WriteOneByte(u8 WriteAddr,u8 DataToWrite)
{	
	 		   	  	    																 
  IIC_Start();
	IIC_Send_Byte(0x78);  //����д����
	IIC_Wait_Ack();
	
	if(DataToWrite)
	{
		IIC_Send_Byte(0x40);//����д����Ĵ�����ַ
		IIC_Wait_Ack();
	}
	else
	{
		IIC_Send_Byte(0x00);//����д���ݼĴ�����ַ
		IIC_Wait_Ack();
	}
	IIC_Send_Byte(WriteAddr);      //������
	IIC_Wait_Ack();
	
	IIC_Stop();
}

  
	
//д�����ֽ�
void OLED_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		OLED_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}


//�������ֽ�
u32 OLED_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=OLED_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

//�������
u8 OLED_Check(void)
{
	u8 temp;
	temp=OLED_ReadOneByte(255);		   
	if(temp==0X55)return 0;		   
	else
	{
		OLED_WriteOneByte(255,0X55);
	    temp=OLED_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}


//��ָ����ַ�������ֽ�
void OLED_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=OLED_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  

//��ָ����ַд�����ֽ�
void OLED_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		OLED_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}



























