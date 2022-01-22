#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    ADC3_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC3_CLK                       RCC_APB2Periph_ADC3

#define    ADC3_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC3_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC3_PORT                      GPIOA

// PC1-通道11 独立IO
#define    ADC3_PIN                       GPIO_Pin_1
#define    ADC3_CHANNEL                   ADC_Channel_1
#define    ADC3_DMA_CHANNEL               DMA2_Channel5

void ADC3_Init(void);


#endif /* __ADC_H */

