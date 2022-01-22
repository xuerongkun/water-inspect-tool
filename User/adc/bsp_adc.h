#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    ADC1_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC1_CLK                       RCC_APB2Periph_ADC1

#define    ADC1_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC1_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC1_PORT                      GPIOA

// PC1-通道11 独立IO
#define    ADC1_PIN                       GPIO_Pin_3
#define    ADC1_CHANNEL                   ADC_Channel_3
#define    ADC1_DMA_CHANNEL               DMA1_Channel1

void ADC1_Init(void);


#endif /* __ADC_H */

