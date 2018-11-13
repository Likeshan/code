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
		u16 speed = 0;
		int tpwm2=TIM2_PWM_CH2_VAL;
		while(tpwm2>0){
			TIM2_PWM_CH2_VAL--;
			TIM2_PWM_CH1_VAL--;

			tpwm2--; 
		}
		PBout(14) = 1;//LEFT
		PBout(15) = 1;
		PBout(13) = 1;//right 
		PBout(12) = 1;
		delay_ms(1000);
		TIM2_PWM_CH2_VAL=200;
		TIM4->CNT=0;
		RIGHT_GO();
		while(1980!=TIM4->CNT);

		PBout(13) = 1;//right
		PBout(12) = 1;
		delay_ms(1000);
		
		RIGHT_GO();
		LEFT_GO();
		while(speed<300)
		{
		speed++;
		TIM2_PWM_CH2_VAL=speed;
		TIM2_PWM_CH1_VAL=speed;
		delay_us(1);
		
		}

		TIM3->CNT=TIM4->CNT=0;
		
		return ;
}
void EXTI_Init(void)
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0XFFFFF0FF;
	GPIOA->CRL |= 0X00000400;
	Ex_NVIC_Config(GPIO_A,2,RTIR); 		//上升沿触发

	MY_NVIC_Init(1,2,EXTI2_IRQn,2);    	//抢占1，子优先级2，组2
}
void EXTI2_IRQHandler(void)
{
	delay_ms(700);
	
	turn_left_90();
	EXTI->PR=1<<2;  //清除LINE0上的中断标志位  
}
