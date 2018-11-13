#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
#define CNT_RESET 0

void TIM3_Encoder_Init(u16 arr,u16 psc);
void TIM4_Encoder_Init(u16 arr,u16 psc);
#endif
