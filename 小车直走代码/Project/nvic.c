#include "nvic.h"
#include "pwm.h"
#include "encoder.h"
#include "usart.h"
#include "delay.h"
#include "motor.h"
int turn_1=10000;
int turn_flag=0;
int step_cnt=0;
void turn_left_90(void)
{
		int tpwm2=TIM2_PWM_CH2_VAL;
		PBout(14) = 0;//LEFT
		PBout(15) = 0;
		PBout(13) = 0;//right 
		PBout(12) = 0;
		delay_ms(1000);
		TIM2_PWM_CH2_VAL=200;

		TIM4->CNT=0;
		RIGHT_GO();
		while(1888!=TIM4->CNT);

		PBout(13) = 0;//right
		PBout(12) = 0;
		delay_ms(1000);
		TIM2_PWM_CH2_VAL=tpwm2;
	
		TIM3->CNT=TIM4->CNT=0;
		RIGHT_GO();
		LEFT_GO();
		return ;
}
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
//	if(step_cnt>=turn_1&&turn_flag<=3)
//	{
//			turn_left_90();
//			step_cnt=0;
//			turn_flag++;
//			//if(turn_flag>=1&&turn_flag<=3)
//				turn_1=14000;
//	}
//	if(step_cnt>=5000&&turn_flag>=4)
//	{
//			PBout(14) = 0;//LEFT
//			PBout(15) = 0;
//			PBout(12) = 0;//right
//			PBout(13) = 0;
//	}
	if(TIM3->CNT>TIM4->CNT) {add_flag = TIM2_PWM_CH2_VAL;TIM2_PWM_CH2_VAL+=50;}
	if(TIM3->CNT<TIM4->CNT) {sub_flag = TIM2_PWM_CH2_VAL;TIM2_PWM_CH2_VAL-=50;}
	while(TIM3->CNT>=TIM4->CNT+5||TIM3->CNT<=TIM4->CNT-5);

//	step_cnt+=TIM3->CNT;	
//TIM3->CNT=TIM4->CNT=0;
	if(add_flag){
		TIM2_PWM_CH2_VAL  = add_flag+1;}
	else if(sub_flag){
		TIM2_PWM_CH2_VAL= sub_flag-1;}
	TIM1->SR &= ~(1<<0);
}

