#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"
void Adc2_Init(void );
u16 Get_Adc2(u8 ch);
u16 Get_Adc2_Average(u8 ch ,u8 times); 
#endif /* __ADC_H */

