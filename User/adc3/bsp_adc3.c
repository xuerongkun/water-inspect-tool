#include "bsp_adc3.h"
#include "bsp_SysTick.h"
#include "./dwt_delay/core_delay.h"   
//千万不要改
__IO uint16_t ADC_ConvertedValue2;

void Adc2_Init(void ){
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC2, ENABLE ); 												   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //卡了一个小时记住是模拟！
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init( GPIOC, &GPIO_InitStructure );	 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(ADC2);
	
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel=1;
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC2,&ADC_InitStructure);
	
	ADC_Cmd(ADC2,ENABLE);
	ADC_ResetCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2));
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2));
}
u16 Get_Adc(u8 ch){
	ADC_RegularChannelConfig(ADC2,ch,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
	while(!ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC2);
}
u16 Get_Adc_Average(u8 ch ,u8 times){
	u32 temp_val=0;
	u8 t;
	for (t=0;t<times;t++){
		temp_val+=Get_Adc(ch);
		Delay_ms(20);
	}
	return temp_val/times;
	
} 
/*********************************************END OF FILE**********************/
