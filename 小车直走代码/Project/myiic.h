#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
 	   		   
//IO方向设置
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<9;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<9;}
#define EE_TYPE 256

//IO操作函数	 
#define IIC_SCL	   PBout(10)
#define IIC_SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);								//发送IIC开始信号
void IIC_Stop(void);	  						//发送IIC停止信号
void IIC_Send_Byte(u8 txd);					//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 							//IIC等待ACK信号
void IIC_Ack(void);									//IIC发送ACK信号
void IIC_NAck(void);								//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  




u8 OLED_ReadOneByte(u16 ReadAddr);							             //指定地址读取一个字节
void OLED_WriteOneByte(u8 WriteAddr,u8 DataToWrite);		     //指定地址写入一个字节
void OLED_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);//指定地址开始写入指定长度的数据
u32 OLED_ReadLenByte(u16 ReadAddr,u8 Len);					         //指定地址开始读取指定长度数据
void OLED_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	 //从指定地址开始写入指定长度的数据
void OLED_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	 //从指定地址开始读出指定长度的数据

u8 OLED_Check(void);  //检查器件
//extern u8 OLED_GRAM[128][8];
#endif
