#include "encoder.h"
#include "sys.h"

//TIM1 编码器输入,TIM3_CH1作A相,TIM3_CH2作B相

void TIM3_Encoder_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR |= 1 << 1;//TIM3 ENABLE
	RCC->APB2ENR |= 1 << 2;//GPIOA ENABLE
	
	GPIOA->CRL &= 0XF0FFFFFF;
	GPIOA->CRL |= 0X04000000;//浮空输入
	
	GPIOA->CRL &= 0X0FFFFFFF;
	GPIOA->CRL |= 0X40000000;//浮空输入
	
	TIM3->PSC  = psc; //分频值
	TIM3->ARR  = arr; // 自动重装载值
	TIM3->CR1 &= ~(3<<8);//选择时钟不分频
	TIM3->CR1 &= ~(3<<5);//边沿对齐模式

	TIM3->CCMR1 |= 1<<0;//CC1S[1:0] 赋值01: IC1映射在TI1上
	TIM3->CCMR2 |= 1<<8;//CC2S[1:0] 赋值01: IC2映射在TI2上
	TIM3->CCER  &= ~(1<<1);//IC1不反向,IC1=TI1
	TIM3->CCER  &= ~(1<<5);//IC2不反向,IC2=TI2
	TIM3->CCMR1 |= 1<<4;//fSAMPLING=fCK_INT, N=2 
	TIM3->CCMR1 |= 1<<12;//fSAMPLING=fCK_INT, N=2 
	TIM3->SMCR  |= 3<<0;//编码器模式3
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
	GPIOB->CRL  |= 0X04000000;//PB6浮空输入
	
	GPIOB->CRL  &= 0X0FFFFFFF;
	GPIOB->CRL  |= 0X40000000;//PB7浮空输入
	
	TIM4->PSC  = psc; //分频值
	TIM4->ARR  = arr; // 自动重装载值
	TIM4->CR1 &= ~(3<<8);//选择时钟不分频
	TIM4->CR1 &= ~(3<<5);//边沿对齐模式

	TIM4->CCMR1 |= 1<<0;//CC1S[1:0] 赋值01: IC1映射在TI1上
	TIM4->CCMR2 |= 1<<8;//CC2S[1:0] 赋值01: IC2映射在TI2上
	TIM4->CCER  &= ~(1<<1);//IC1不反向,IC1=TI1
	TIM4->CCER  &= ~(1<<5);//IC2不反向,IC2=TI2
	TIM4->CCMR1 |= 1<<4;//fSAMPLING=fCK_INT, N=2 
	TIM4->CCMR1 |= 1<<12;//fSAMPLING=fCK_INT, N=2 
	TIM4->SMCR  |= 3<<0;//编码器模式3
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

