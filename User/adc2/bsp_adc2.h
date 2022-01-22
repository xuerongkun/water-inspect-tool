#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADC3_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC3_CLK                       RCC_APB2Periph_ADC3

#define    ADC3_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC3_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC3_PORT                      GPIOA

// PC1-ͨ��11 ����IO
#define    ADC3_PIN                       GPIO_Pin_1
#define    ADC3_CHANNEL                   ADC_Channel_1
#define    ADC3_DMA_CHANNEL               DMA2_Channel5

void ADC3_Init(void);


#endif /* __ADC_H */

