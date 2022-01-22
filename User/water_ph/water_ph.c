#include "water_ph.h"
#include "stdio.h"
#include "bsp_adc.h"
#include "bsp_adc2.h"
#include "bsp_adc3.h"
#include "./dwt_delay/core_delay.h"

float orpArray[ArrayLenth_orp];
int orpArrayIndex=0;
float ORP=0.0,ORP1=0.0;
float ORP_value=0.0;

char Liquid_TX[5];
float Liquid_Value=0.0;

float PH_Value=0.0;
char TX_PH[5];

extern __IO uint16_t ADC_ConvertedValue1;
extern __IO uint16_t ADC_ConvertedValue3;

//-----------------------------------------***ORP------------------------------------------------
double avergearray(float* arr, int number)
{
  int i;
  float avg;
  float amount=0;
    for(i=0;i<number;i++)
	  {
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
}

void ORP_Value_Conversion(void)
{
    ORP=1000*ORP/0.66;
    ORP_value=2000-ORP-OFFSET_orp;//0为中值,<0为和还原性，>0为氧化性
}


void ORP_Value_get(void)
{
	orpArray[orpArrayIndex]=ADC_ConvertedValue1/4096*3.3;
	orpArrayIndex++;	
	if (orpArrayIndex==ArrayLenth_orp) 
	{
		orpArrayIndex=0;
		ORP=avergearray(orpArray, ArrayLenth_orp);
		ORP_Value_Conversion();	
		Delay_ms(20);
   } 
}
//-----------------------------------------***水深------------------------------------------------
void Liquid_Value_Conversion(float value)
{
	Liquid_Value=value;
	Liquid_TX[0]=(int)(Liquid_Value*1000)/1000+'0';
	Liquid_TX[1]='.';	
	Liquid_TX[2]=(int)(Liquid_Value*1000)%1000/100+'0';
	Liquid_TX[3]=(int)(Liquid_Value*1000)%100/10+'0';
	Liquid_TX[4]=(int)(Liquid_Value*1000)%10+'0';	  
}

//-----------------------------------------***PH------------------------------------------------
void PH_Value_Conversion(void)
{
	float vaule=ADC_ConvertedValue3*3.3/4096;
	PH_Value=-5.7541*vaule+16.654;
	if(PH_Value<=0.0){PH_Value=0.0;}
	if(PH_Value>=14.0){PH_Value=14.0;}
	/*显示电压*/
	TX_PH[0]=(int)(PH_Value*100)/1000+'0';	
	TX_PH[1]=(int)(PH_Value*100)%1000/100+'0';
	TX_PH[2]='.';
	TX_PH[3]=(int)(PH_Value*100)%100/10+'0';
	TX_PH[4]=(int)(PH_Value*100)%10+'0';
}