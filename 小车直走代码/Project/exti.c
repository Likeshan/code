//言叶之庭
#include "exti.h"
#include "nvic.h"
#include "nvic.h"
#include "pwm.h"
#include "encoder.h"
#include "usart.h"
#include "delay.h"
#include "motor.h"
void turn_left_90(void)
{	
		delay_ms(1000);
		TIM2_PWM_CH2_VAL=150;
		TIM3->CNT=TIM4->CNT=0;
		RIGHT_GO();
		while(1550!=TIM4->CNT);

		PBout(13) = 1;//right
		PBout(12) = 1;
		delay_ms(1000);
		return ;
}
void SlowBuffer(int TURN_DISTANCE,int aim_pwm)
{
	int current_pwm1 = TIM2_PWM_CH1_VAL;
	int current_pwm2 = TIM2_PWM_CH2_VAL;
	TIM3->CNT = TIM4->CNT = 0;
	
	while(TIM3->CNT < TURN_DISTANCE || TIM4->CNT < TURN_DISTANCE)
	{
		if(TIM3->CNT < TURN_DISTANCE)
			TIM2_PWM_CH1_VAL = current_pwm1 - TIM3->CNT/(TURN_DISTANCE*(current_pwm1-aim_pwm));
		else 
		{	
			PBout(14) = 1;//LEFT
  		PBout(15) = 1;
		
		}	
		if(TIM4->CNT < TURN_DISTANCE)
			TIM2_PWM_CH2_VAL = current_pwm2 - TIM4->CNT/(TURN_DISTANCE*(current_pwm2-aim_pwm));
		else
		{			
			PBout(12) = 1;//RIGHT
  		PBout(13) = 1;
		}
	}

	PBout(14) = 1;//LEFT
	PBout(15) = 1;
	
	PBout(12) = 1;//RIGHT
	PBout(13) = 1;
}
void EXTI_Init(void)
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRH &= 0XFFFFFFF0;
	GPIOA->CRH |= 0X00000004;
	
	//GPIOA->CRL &= 0XFF0FFFFF;
	//GPIOA->CRL |= 0X00400000;
	Ex_NVIC_Config(GPIO_A,8,RTIR); 		//上升沿触发
	Ex_NVIC_Config(GPIO_A,5,RTIR); 		//上升沿触发
	
	MY_NVIC_Init(1,2,EXTI9_5_IRQn,2);    	//抢占1，子优先级2，组2
}
void EXTI9_5_IRQHandler(void)
{
	if(PAin(8)==1&&PAin(5)==1)
	{
		TIM2_PWM_CH1_VAL=200;
		TIM2_PWM_CH2_VAL=200;
		RIGHT_GO();
		LEFT_GO();
		SlowBuffer(2300,150);
		turn_left_90();
		startgo();
		EXTI->PR=1<<8;
		EXTI->PR=1<<5; 
		return ;
	}
	if(PAin(5)==1)
	{
		
				LEFT_BACK();
				delay_ms(50);
				LEFT_GO();
				if(PAin(8)==1&&PAin(5)==1)
				{
						SlowBuffer(2300,150);
						turn_left_90();
						startgo();
						TIM1->SR &= ~(1<<0);
						EXTI->PR=1<<8;
						EXTI->PR=1<<5;
						return;	
				}
				else 
				{
					TIM1->SR |= 1<<0;
						//TIM3->CNT=TIM4->CNT=0;
						EXTI->PR=1<<8;
						EXTI->PR=1<<5;
				
						return;	
				}
				
			
	}
	if(PAin(8)==1)
	{
		
				RIGHT_BACK();
				delay_ms(50);
				RIGHT_GO();
				if(PAin(8)==1&&PAin(5)==1)
				{
						SlowBuffer(2300,150);
						turn_left_90();
						startgo();
					TIM1->SR &= ~(1<<0);
						EXTI->PR=1<<8;
						EXTI->PR=1<<5;
						return;	
				}
				else 
				{
					TIM1->SR |= 1<<0;
					//TIM3->CNT=TIM4->CNT=0;
						EXTI->PR=1<<8;
						EXTI->PR=1<<5;
					
						return;	
				}
			
			
	}
/*	if(PAin(5)==1)
	{
		PBout(14) = 1;//LEFT
		PBout(15) = 1;
		TIM2_PWM_CH2_VAL=150;
		while(PAin(8)!=1);
		PBout(13) = 1;//R
		PBout(12) = 1;
		
		TIM2_PWM_CH1_VAL=200;
		TIM2_PWM_CH2_VAL=200;
		RIGHT_GO();
		LEFT_GO();
		SlowBuffer(2300,150);
		turn_left_90();
		startgo();
		
		EXTI->PR=1<<8;
		EXTI->PR=1<<5;
		return;	
	}
	if(PAin(8)==1)
	{
		PBout(13) = 1;//r
		PBout(12) = 1;
		TIM2_PWM_CH1_VAL=150;
		while(PAin(5)!=1);
		PBout(14) = 1;//l
		PBout(15) = 1;
		
		TIM2_PWM_CH1_VAL=200;
		TIM2_PWM_CH2_VAL=200;
		RIGHT_GO();
		LEFT_GO();
		SlowBuffer(2300,150);
		turn_left_90();
		startgo();
		
		EXTI->PR=1<<8;
		EXTI->PR=1<<5;
		return;	
	}*/
/*	SlowBuffer(2300,150);
	turn_left_90();
	startgo();
	EXTI->PR=1<<8;*/
	
	EXTI->PR=1<<8;
	EXTI->PR=1<<5;
}
