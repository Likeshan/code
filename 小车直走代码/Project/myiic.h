#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
 	   		   
//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<9;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<9;}
#define EE_TYPE 256

//IO��������	 
#define IIC_SCL	   PBout(10)
#define IIC_SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);								//����IIC��ʼ�ź�
void IIC_Stop(void);	  						//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);					//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 							//IIC�ȴ�ACK�ź�
void IIC_Ack(void);									//IIC����ACK�ź�
void IIC_NAck(void);								//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  




u8 OLED_ReadOneByte(u16 ReadAddr);							             //ָ����ַ��ȡһ���ֽ�
void OLED_WriteOneByte(u8 WriteAddr,u8 DataToWrite);		     //ָ����ַд��һ���ֽ�
void OLED_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);//ָ����ַ��ʼд��ָ�����ȵ�����
u32 OLED_ReadLenByte(u16 ReadAddr,u8 Len);					         //ָ����ַ��ʼ��ȡָ����������
void OLED_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	 //��ָ����ַ��ʼд��ָ�����ȵ�����
void OLED_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	 //��ָ����ַ��ʼ����ָ�����ȵ�����

u8 OLED_Check(void);  //�������
//extern u8 OLED_GRAM[128][8];
#endif
