#include "sys.h"                                                                                                                                                                                                                                                                           .h"
#include "delay.h"
#include "nvic.h"
#include "pwm.h"
#include "encoder.h"
#include "motor.h"
#include "exti.h"                                                                                                                                                                                                                                                                .h"
#include "usart.h"

#include "myiic.h"
#include "oled.h"

int main(void)
             { 
	Stm32_Clock_Init(9);
	delay_init(72);
	Motor_Init();
	
	IIC_Init();	          //IIC初始化
	OLED_Init();		      //初始化OLED
 	//uart_init(72,9600);
	TIM3_Encoder_Init(65535,0);		 //编码器
	TIM4_Encoder_Init(65535,0);    //编码器
	TIM2_PWM_Init(899,0);         //PWM输出
	delay_ms(1864);								//delay_ms 参数最大为1864
	PBout(14) = 0;//LEFT
	PBout(15) = 1; 
	PBout(13) = 1;//RIGHT
	PBout(12) = 0;     

	startgo();
	
	TIM1_Int_Init(7199,99);				 //定时器10ms
	EXTI_Init();
	while(1)
	{
				OLED_ShowNum(0,0,TIM3->CNT,6,12);
				OLED_ShowNum(50,0,TIM4->CNT,6,12);
				OLED_ShowNum(0,20,TIM2_PWM_CH1_VAL,6,12);
				OLED_ShowNum(50,20,TIM2_PWM_CH2_VAL,6,12);
				OLED_Refresh_Gram();
				//delay_us(1);		
	}
	 
}
	
