#include "./dwt_delay/core_delay.h"   

#if USE_DWT_DELAY


#define  DWT_CR      *(__IO uint32_t *)0xE0001000
#define  DWT_CYCCNT  *(__IO uint32_t *)0xE0001004
#define  DEM_CR      *(__IO uint32_t *)0xE000EDFC


#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)

void CPU_TS_TmrInit(void)
{
    /* ʹ��DWT���� */
    DEM_CR |= (uint32_t)DEM_CR_TRCENA;                

    /* DWT CYCCNT�Ĵ���������0 */
    DWT_CYCCNT = (uint32_t)0u;

    /* ʹ��Cortex-M DWT CYCCNT�Ĵ��� */
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
}


uint32_t CPU_TS_TmrRd(void)
{        
  return ((uint32_t)DWT_CYCCNT);
}


void CPU_TS_Tmr_Delay_US(__IO uint32_t us)
{
  uint32_t ticks;
  uint32_t told,tnow,tcnt=0;

  /* �ں����ڲ���ʼ��ʱ����Ĵ����� */  
#if (CPU_TS_INIT_IN_DELAY_FUNCTION)  
  /* ��ʼ��ʱ��������� */
  CPU_TS_TmrInit();
#endif
  
  ticks = us * (GET_CPU_ClkFreq() / 1000000);  /* ��Ҫ�Ľ����� */      
  tcnt = 0;
  told = (uint32_t)CPU_TS_TmrRd();         /* �ս���ʱ�ļ�����ֵ */

  while(1)
  {
    tnow = (uint32_t)CPU_TS_TmrRd();  
    if(tnow != told)
    { 
        /* 32λ�������ǵ��������� */    
      if(tnow > told)
      {
        tcnt += tnow - told;  
      }
      /* ����װ�� */
      else 
      {
        tcnt += UINT32_MAX - told + tnow; 
      } 
      
      told = tnow;

      /*ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳� */
      if(tcnt >= ticks)break;
    }
  }
}

#endif

/*********************************************END OF FILE**********************/
