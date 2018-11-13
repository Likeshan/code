#include "pwm.h"

void TIM2_PWM_Init(u16 arr,u16 psc)
{

	RCC->APB1ENR |= 1 << 0; //TIM2 ENABLE
	RCC->APB2ENR |= 1 << 2; //GPIOA ENABLE
	GPIOA->CRL  &= 0XFFFFFFF0;
	GPIOA->CRL  |= 0X0000000B;

	GPIOA->CRL  &= 0XFFFFFF0F;
	GPIOA->CRL  |= 0X000000B0;
	TIM2->ARR = arr; //�Զ���װ��
	TIM2->PSC = psc; //��Ƶֵ
	TIM2->CCMR1 |= 6<<12;//CH2_PWM1ģʽ
	TIM2->CCMR1 |= 1<<11;
	TIM2->CCMR1 |= 6<<4; //CH1_PWMģʽ1 ռ�ձ�Խ��Խ��
	TIM2->CCMR1 |= 1<<3; //����CCR1�Ĵ�����Ԥװ�ع���
	TIM2->CCER  |= 1<<0; //OC1�ź��������Ӧ����
	TIM2->CCER  |= 1<<4;
	TIM2->CR1    = 0x0080;
	TIM2->CR1   |= 1<<0; //ʹ�ܼ�����;
}
