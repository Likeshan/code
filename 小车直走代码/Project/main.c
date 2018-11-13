#include "sys.h"                                                                                                                                                                                                                                                                           .h"
#include "delay.h"
#include "nvic.h"
#include "pwm.h"
#include "encoder.h"
#include "motor.h"
#include "exti.h"                                                                                                                                                                                                                                                                .h"
#include "usart.h"
int main(void)
{
//	u16 pwm_ch1_val = 300;
//	u16 pwm_ch2_val = 300;
	u16 speed=0;
	Stm32_Clock_Init(9);
	delay_init(72);
	delay_ms(1864);								//delay_ms 参数最大为1864
	Motor_Init();
	uart_init(72,9600);
	
	TIM3_Encoder_Init(65535,0);		 //编码器
	TIM4_Encoder_Init(65535,0);    //编码器
	TIM2_PWM_Init(899,0);         //PWM输出

	
	
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
	delay_ms(300);
	//turn_left_90();
	//turn_left_90();
	//turn_left_90();
	//turn_left_90();
	TIM1_Int_Init(7199,99);				 //定时器10ms
	EXTI_Init();
	while(1)
	{
		
		//printf("v1:%d    v2:%d\r\n",TIM3->CNT,TIM4->CNT);
		//delay_ms(100);
	}
}
