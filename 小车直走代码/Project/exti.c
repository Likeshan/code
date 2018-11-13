#include "exti.h"
#include "nvic.h"
#include "nvic.h"
#include "pwm.h"
#include "encoder.h"
#include "usart.h"
#include "delay.h"
#include "motor.h"
void EXTI_Init(void)
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0XFFFFF0FF;
	
	Ex_NVIC_Config(GPIO_A,2,RTIR); 		//�����ش���

	MY_NVIC_Init(1,2,EXTI0_IRQn,2);    	//��ռ1�������ȼ�2����2
}
void EXTI0_IRQHandler(void)
{
	
	turn_left_90();
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}