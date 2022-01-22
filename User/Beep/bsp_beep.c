#include "..\User\Beep\bsp_beep.h" 

static void                     Beep_GPIO_Config                        ( void );

void Beep_Init ( void )
{		
	Beep_GPIO_Config ();
	macBEEP_OFF ();         
}

static void Beep_GPIO_Config ( void )
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	macBEEP_GPIO_APBxClock_FUN  ( macBEEP_GPIO_CLK, ENABLE ); 											   
	GPIO_InitStructure.GPIO_Pin = macBEEP_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( macBEEP_PORT, & GPIO_InitStructure );
}

