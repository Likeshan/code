#include "encoder.h"
#include "sys.h"

//TIM1 ����������,TIM3_CH1��A��,TIM3_CH2��B��

void TIM3_Encoder_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR |= 1 << 1;//TIM3 ENABLE
	RCC->APB2ENR |= 1 << 2;//GPIOA ENABLE
	
	GPIOA->CRL &= 0XF0FFFFFF;
	GPIOA->CRL |= 0X04000000;//��������
	
	GPIOA->CRL &= 0X0FFFFFFF;
	GPIOA->CRL |= 0X40000000;//��������
	
	TIM3->PSC  = psc; //��Ƶֵ
	TIM3->ARR  = arr; // �Զ���װ��ֵ
	TIM3->CR1 &= ~(3<<8);//ѡ��ʱ�Ӳ���Ƶ
	TIM3->CR1 &= ~(3<<5);//���ض���ģʽ

	TIM3->CCMR1 |= 1<<0;//CC1S[1:0] ��ֵ01: IC1ӳ����TI1��
	TIM3->CCMR2 |= 1<<8;//CC2S[1:0] ��ֵ01: IC2ӳ����TI2��
	TIM3->CCER  &= ~(1<<1);//IC1������,IC1=TI1
	TIM3->CCER  &= ~(1<<5);//IC2������,IC2=TI2
	TIM3->CCMR1 |= 1<<4;//fSAMPLING=fCK_INT, N=2 
	TIM3->CCMR1 |= 1<<12;//fSAMPLING=fCK_INT, N=2 
	TIM3->SMCR  |= 3<<0;//������ģʽ3
//	TIM3->DIER |= 1<<0;//Update interrupt enable
//	TIM3->DIER |= 1<<1;//Capture/Compare 1 interrupt enable
//	TIM3->DIER |= 1<<6;//Trigger interrupt enable
//	MY_NVIC_Init(2,0,TIM3_IRQn,2);
	TIM3->CNT    = CNT_RESET;
	TIM3->CR1   |= 0X01; 
}


void TIM4_Encoder_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR |= 1 << 2;//TIM4 ENABLE
	RCC->APB2ENR |= 1 << 3;//GPIOB ENABLE
	
	GPIOB->CRL  &= 0XF0FFFFFF;
	GPIOB->CRL  |= 0X04000000;//PB6��������
	
	GPIOB->CRL  &= 0X0FFFFFFF;
	GPIOB->CRL  |= 0X40000000;//PB7��������
	
	TIM4->PSC  = psc; //��Ƶֵ
	TIM4->ARR  = arr; // �Զ���װ��ֵ
	TIM4->CR1 &= ~(3<<8);//ѡ��ʱ�Ӳ���Ƶ
	TIM4->CR1 &= ~(3<<5);//���ض���ģʽ

	TIM4->CCMR1 |= 1<<0;//CC1S[1:0] ��ֵ01: IC1ӳ����TI1��
	TIM4->CCMR2 |= 1<<8;//CC2S[1:0] ��ֵ01: IC2ӳ����TI2��
	TIM4->CCER  &= ~(1<<1);//IC1������,IC1=TI1
	TIM4->CCER  &= ~(1<<5);//IC2������,IC2=TI2
	TIM4->CCMR1 |= 1<<4;//fSAMPLING=fCK_INT, N=2 
	TIM4->CCMR1 |= 1<<12;//fSAMPLING=fCK_INT, N=2 
	TIM4->SMCR  |= 3<<0;//������ģʽ3
//	TIM4->DIER |= 1<<0;//Update interrupt enable
//	TIM4->DIER |= 1<<1;//Capture/Compare 1 interrupt enable
//	TIM4->DIER |= 1<<6;//Trigger interrupt enable
//	MY_NVIC_Init(2,0,TIM4_IRQn,2);
	TIM4->CNT    = CNT_RESET;
	TIM4->CR1   |= 0X01; 
}

//void TIM3_IRQHandler(void)
//{
//	if(TIM3->SR & 0X0001)
//	{
//		TIM3->SR &= ~(1<<0);
//	}
//}

//void TIM4_IRQHandler(void)
//{
//	if(TIM4->SR & 0X0001)
//	{
//		TIM4->SR &= ~(1<<0);
//	}
//}

