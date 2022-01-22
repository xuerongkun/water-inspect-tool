#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADC1_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC1_CLK                       RCC_APB2Periph_ADC1

#define    ADC1_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC1_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC1_PORT                      GPIOA

// PC1-ͨ��11 ����IO
#define    ADC1_PIN                       GPIO_Pin_3
#define    ADC1_CHANNEL                   ADC_Channel_3
#define    ADC1_DMA_CHANNEL               DMA1_Channel1

void ADC1_Init(void);


#endif /* __ADC_H */

