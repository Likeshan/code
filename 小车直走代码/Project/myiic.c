#include "myiic.h"
#include "delay.h"
#include "oled.h"
//初始化IIC
extern u8 OLED_GRAM[128][8];	 
void IIC_Init(void)
{					     
 	RCC->APB2ENR|=1<<4;    //先使能外设IO PORTC时钟 							 
	GPIOB->CRH&=0XFFFFF00F;//PC9/10 推挽输出
	GPIOB->CRH|=0X00000330;	   
	GPIOB->ODR|=3<<11;     //PC9,10 输出高
}
//产生IIC起始信号
void IIC_Start(void)
{
	
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	   
	IIC_SCL=1; 
	delay_us(1);//LED0 = 0;	
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(1);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(1); 
	IIC_SCL=1;//STOP:when CLK is high DATA change form low to high
 	delay_us(1); 
	IIC_SDA=1;//发送I2C总线结束信号 						   	
}
//等待应答信号到来
//1，接收应答失败
//0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
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
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{   
		
    u8 t;  
		SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(1);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(1); 
		IIC_SCL=0;	
		delay_us(1);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}





//读一个字节
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
   
//写一个字节
void OLED_WriteOneByte(u8 WriteAddr,u8 DataToWrite)
{	
	 		   	  	    																 
  IIC_Start();
	IIC_Send_Byte(0x78);  //发送写命令
	IIC_Wait_Ack();
	
	if(DataToWrite)
	{
		IIC_Send_Byte(0x40);//发送写命令寄存器地址
		IIC_Wait_Ack();
	}
	else
	{
		IIC_Send_Byte(0x00);//发送写数据寄存器地址
		IIC_Wait_Ack();
	}
	IIC_Send_Byte(WriteAddr);      //发数据
	IIC_Wait_Ack();
	
	IIC_Stop();
}

  
	
//写定长字节
void OLED_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		OLED_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}


//读定长字节
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

//检查器件
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


//从指定地址读定长字节
void OLED_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=OLED_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  

//从指定地址写定长字节
void OLED_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		OLED_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}



























