#include "pwm.h"

void TIM2_PWM_Init(u16 arr,u16 psc)
{

	RCC->APB1ENR |= 1 << 0; //TIM2 ENABLE
	RCC->APB2ENR |= 1 << 2; //GPIOA ENABLE
	GPIOA->CRL  &= 0XFFFFFFF0;
	GPIOA->CRL  |= 0X0000000B;

	GPIOA->CRL  &= 0XFFFFFF0F;
	GPIOA->CRL  |= 0X000000B0;
	TIM2->ARR = arr; //自动重装载
	TIM2->PSC = psc; //分频值
	TIM2->CCMR1 |= 6<<12;//CH2_PWM1模式
	TIM2->CCMR1 |= 1<<11;
	TIM2->CCMR1 |= 6<<4; //CH1_PWM模式1 占空比越大越快
	TIM2->CCMR1 |= 1<<3; //开启CCR1寄存器的预装载功能
	TIM2->CCER  |= 1<<0; //OC1信号输出到对应引脚
	TIM2->CCER  |= 1<<4;
	TIM2->CR1    = 0x0080;
	TIM2->CR1   |= 1<<0; //使能计数器;
}
