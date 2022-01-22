/*
����USBʱ��ע��ʹ��
��ɫ TXD
��ɫ GND
��ɫ RXD
��ɫ 5

���������������ķ�������water_ph.c
������������ȫ�ֱ�������water_ph.h
����wifi��bsp_esp8266_text.c
*/
 
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"
#include "bsp_dht11.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_adc.h"
#include "bsp_adc2.h"
#include "bsp_adc3.h"
#include "dac.h"
#include "water_ph.h"
#include "./dwt_delay/core_delay.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue1;
extern __IO uint16_t ADC_ConvertedValue2;
extern __IO uint16_t ADC_ConvertedValue3;
// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal1;        
float ADC_ConvertedValueLocal2;       
float ADC_ConvertedValueLocal3;   

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 


int main ( void )
{
	/* ��ʼ�� */
  USARTx_Config ();                                                              //��ʼ������1
  CPU_TS_TmrInit();
	ESP8266_Init ();                                                               //��ʼ��WiFiģ��ʹ�õĽӿں�����
	DHT11_Init ();
  LED_Init ();
	Beep_Init ();
	Dac1_Init();
	ADC1_Init();
	Adc2_Init();
	ADC3_Init();
	Dac1_Set_Vol(3300);
	
	printf ( "\r\n��Ŀʵ��\r\n" );                          
  #ifndef BUILTAP_TEST
  ESP8266_StaTcpServer_ConfigTest();                                             //��ESP8266�������� STAģʽ
  #else
  ESP8266_ApTcpServer_ConfigTest();                                              //��ESP8266�������� APģʽ
  #endif
	
	
  while ( 1 )
  {   
		ADC_ConvertedValue2=Get_Adc_Average(ADC_Channel_12,20);         //ADC2������ѯ�ķ�ʽ
		
		//����һ�����ڸ���һ��������������Ŀ��������������ADC1 3����DMA��ADC2���ø�Ƶ����ƽ������
		
		ADC_ConvertedValueLocal1 =(float) ADC_ConvertedValue1/4096*3.3; // ��ȡת����ADֵ
		ADC_ConvertedValueLocal2 =(float) ADC_ConvertedValue2/4096*3.3; // ��ȡת����ADֵ
		ADC_ConvertedValueLocal3 =(float) ADC_ConvertedValue3/4096*3.3; // ��ȡת����ADֵ
		
		ORP_Value_get( );
		//���ú�float�� ORP_valueȫ�ֱ�����д��ֵ //��������ÿ��0.02s��ȡһ�����ݣ���50�δ�����ADC1��
		
		Liquid_Value_Conversion(ADC_ConvertedValueLocal2);  //ֱ��ʹ���Ѿ�����50��ƽ����ֵ
		//���ú�float�� Liquid_Valueȫ�ֱ�����д��ֵ
		
		ORP_Value_get();																		//�������󣬴�ADC3��ȡһ�����ݡ�
		//���ú�float�� PH_Valueȫ�ֱ�����д��ֵ
		
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue1); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal1);
		printf("\r\n The current ORP_value = %f V \r\n",ORP_value);
		
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue2); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal2); 
		printf("\r\n The current Liquid_Value = %f V \r\n",Liquid_Value); 
		
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue3); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal3);
		printf("\r\n The current PH_Value = %f V \r\n",PH_Value);
		
		ESP8266_CheckRecv_SendDataTest(); // ESP8266 ������������
    
  }
}


