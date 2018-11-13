#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
#define TIM2_PWM_CH1_VAL TIM2->CCR1
#define TIM2_PWM_CH2_VAL TIM2->CCR2
void TIM2_PWM_Init(u16 arr,u16 psc); 
#endif
