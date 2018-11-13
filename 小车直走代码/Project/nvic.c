#include "nvic.h"
#include "pwm.h"
#include "encoder.h"
#include "usart.h"
#include "delay.h"
#include "motor.h"

void TIM1_Int_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR |= 1<<11;
	TIM1->ARR   = arr;
	TIM1->PSC   = psc;
	TIM1->DIER |= 1<<0;
	TIM1->CR1  |= 0X01;
	MY_NVIC_Init(2,3,TIM1_UP_IRQn,2); 
  
}
void TIM1_UP_IRQHandler()
{
	int add_flag=0,sub_flag=0;

	if(TIM3->CNT>TIM4->CNT) {add_flag = TIM2_PWM_CH2_VAL;TIM2_PWM_CH2_VAL+=50;}
	if(TIM3->CNT<TIM4->CNT) {sub_flag = TIM2_PWM_CH2_VAL;TIM2_PWM_CH2_VAL-=50;}
	while(TIM3->CNT>=TIM4->CNT+5||TIM3->CNT<=TIM4->CNT-5);
  
//TIM3->CNT=TIM4->CNT=0;
	if(add_flag){
		TIM2_PWM_CH2_VAL  = add_flag+1;}
	else if(sub_flag){
		TIM2_PWM_CH2_VAL= sub_flag-1;}
	TIM1->SR &= ~(1<<0);
}

