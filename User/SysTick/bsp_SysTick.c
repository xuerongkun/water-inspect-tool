#include "bsp_SysTick.h"

void SysTick_Init( void )
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if ( SysTick_Config(SystemCoreClock / 100) )	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
  // ʹ�ܵδ�ʱ��  10ms�ж�һ��
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
}