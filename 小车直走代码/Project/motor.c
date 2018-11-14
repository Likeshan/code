#include "motor.h"
#include "sys.h"
#include "pwm.h"
#include "delay.h"
void startgo(void )	
{//pwm和编码器全部清零，然后pwm加速到speed的值
	int speed=0;
	TIM3->CNT=0;
	TIM4->CNT=0;
	TIM2_PWM_CH1_VAL=0;
  TIM2_PWM_CH2_VAL=0;
	LEFT_GO();
	RIGHT_GO();
	while(speed<300)
	{
		speed++;
		TIM2_PWM_CH1_VAL=speed;
		TIM2_PWM_CH2_VAL=speed;
		delay_us(1);
	}
}
void Motor_Init(void)
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRH &= 0X0000FFFF;
	GPIOB->CRH |= 0X33330000;
}
void LEFT_GO(void)                     
{
	PBout(14) = 0;//LEFT
	PBout(15) = 1;
}

void LEFT_BACK(void)
{
	PBout(14) = 1;//LEFT
	PBout(15) = 0;
}

void RIGHT_GO(void)
{
	PBout(13) = 1;//RIGHT
	PBout(12) = 0                                                      ;
}
void RIGHT_BACK(void)
{
	PBout(13) = 0;//RIGHT
	PBout(12) = 1;
}
