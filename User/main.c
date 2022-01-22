/*
连接USB时，注意使用
绿色 TXD
黑色 GND
白色 RXD
红色 5

调用三个传感器的方法都在water_ph.c
三个传感器的全局变量都在water_ph.h
调用wifi在bsp_esp8266_text.c
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

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue1;
extern __IO uint16_t ADC_ConvertedValue2;
extern __IO uint16_t ADC_ConvertedValue3;
// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal1;        
float ADC_ConvertedValueLocal2;       
float ADC_ConvertedValueLocal3;   

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 


int main ( void )
{
	/* 初始化 */
  USARTx_Config ();                                                              //初始化串口1
  CPU_TS_TmrInit();
	ESP8266_Init ();                                                               //初始化WiFi模块使用的接口和外设
	DHT11_Init ();
  LED_Init ();
	Beep_Init ();
	Dac1_Init();
	ADC1_Init();
	Adc2_Init();
	ADC3_Init();
	Dac1_Set_Vol(3300);
	
	printf ( "\r\n项目实验\r\n" );                          
  #ifndef BUILTAP_TEST
  ESP8266_StaTcpServer_ConfigTest();                                             //对ESP8266进行配置 STA模式
  #else
  ESP8266_ApTcpServer_ConfigTest();                                              //对ESP8266进行配置 AP模式
  #endif
	
	
  while ( 1 )
  {   
		ADC_ConvertedValue2=Get_Adc_Average(ADC_Channel_12,20);         //ADC2采用轮询的方式
		
		//把哪一个串口给哪一个传感器，由项目组决定，这里提出ADC1 3采用DMA，ADC2采用高频率求平均法。
		
		ADC_ConvertedValueLocal1 =(float) ADC_ConvertedValue1/4096*3.3; // 读取转换的AD值
		ADC_ConvertedValueLocal2 =(float) ADC_ConvertedValue2/4096*3.3; // 读取转换的AD值
		ADC_ConvertedValueLocal3 =(float) ADC_ConvertedValue3/4096*3.3; // 读取转换的AD值
		
		ORP_Value_get( );
		//调用后（float） ORP_value全局变量被写入值 //进入程序后每隔0.02s读取一次数据，读50次处理，从ADC1读
		
		Liquid_Value_Conversion(ADC_ConvertedValueLocal2);  //直接使用已经做了50次平均的值
		//调用后（float） Liquid_Value全局变量被写入值
		
		ORP_Value_get();																		//进入程序后，从ADC3读取一次数据。
		//调用后（float） PH_Value全局变量被写入值
		
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue1); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal1);
		printf("\r\n The current ORP_value = %f V \r\n",ORP_value);
		
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue2); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal2); 
		printf("\r\n The current Liquid_Value = %f V \r\n",Liquid_Value); 
		
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue3); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal3);
		printf("\r\n The current PH_Value = %f V \r\n",PH_Value);
		
		ESP8266_CheckRecv_SendDataTest(); // ESP8266 处理并发送数据
    
  }
}


