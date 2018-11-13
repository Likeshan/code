#include "motor.h"
#include "sys.h"
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
