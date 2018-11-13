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
	
	Ex_NVIC_Config(GPIO_A,2,RTIR); 		//上升沿触发

	MY_NVIC_Init(1,2,EXTI0_IRQn,2);    	//抢占1，子优先级2，组2
}
void EXTI0_IRQHandler(void)
{
	
	turn_left_90();
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}