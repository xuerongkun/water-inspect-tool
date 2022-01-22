#include "bsp_adc2.h"
__IO uint16_t ADC_ConvertedValue3;

/**
  * @brief  ADC GPIO 初始化
  * @param  无
  * @retval 无
  */
static void ADC3_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 打开 ADC IO端口时钟
	ADC3_GPIO_APBxClock_FUN ( ADC3_GPIO_CLK, ENABLE );
	
	// 配置 ADC IO 引脚模式
	GPIO_InitStructure.GPIO_Pin = ADC3_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// 初始化 ADC IO
	GPIO_Init(ADC3_PORT, &GPIO_InitStructure);				
}

/**
  * @brief  配置ADC工作模式
  * @param  无
  * @retval 无
  */
static void ADC3_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure3;
	ADC_InitTypeDef ADC_InitStructure3;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	ADC3_APBxClock_FUN ( ADC3_CLK, ENABLE );
	DMA_DeInit(ADC3_DMA_CHANNEL);
	DMA_InitStructure3.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC3->DR ) );
	DMA_InitStructure3.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue3;
	DMA_InitStructure3.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure3.DMA_BufferSize = 1;
	DMA_InitStructure3.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure3.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	DMA_InitStructure3.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure3.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure3.DMA_Mode = DMA_Mode_Circular;	
	DMA_InitStructure3.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure3.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(ADC3_DMA_CHANNEL, &DMA_InitStructure3);
	DMA_Cmd(ADC3_DMA_CHANNEL , ENABLE);
	ADC_InitStructure3.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure3.ADC_ScanConvMode = DISABLE ; 
	ADC_InitStructure3.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure3.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure3.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure3.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC3, &ADC_InitStructure3);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
	ADC_RegularChannelConfig(ADC3, ADC3_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	ADC_DMACmd(ADC3, ENABLE);
	ADC_Cmd(ADC3, ENABLE);
	ADC_ResetCalibration(ADC3);
	while(ADC_GetResetCalibrationStatus(ADC3));
	ADC_StartCalibration(ADC3);
	while(ADC_GetCalibrationStatus(ADC3));
	ADC_SoftwareStartConvCmd(ADC3, ENABLE);
}

void ADC3_Init(void)
{
	ADC3_GPIO_Config();
	ADC3_Mode_Config();
}

