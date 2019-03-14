#ifndef __CORE_DELAY_H
#define __CORE_DELAY_H

#include "stm32f4xx.h"


#define Delay_ms(ms)  	CPU_TS_Tmr_Delay_MS(ms)
#define Delay_us(us)  	CPU_TS_Tmr_Delay_US(us)

/* 最大延时 60s=2的32次方/72000000 */
#define Delay_s(s)  	  CPU_TS_Tmr_Delay_S(s)

/* 获取内核时钟频率 */
#define GET_CPU_ClkFreq()       (SystemCoreClock)
#define SysClockFreq            (SystemCoreClock)

/*******************************************************************************
 * 							函数声明
 ******************************************************************************/
uint32_t CPU_TS_TmrRd(void);
void CPU_TS_TmrInit(void);

//使用以下函数前必须先调用CPU_TS_TmrInit函数使能计数器，或使能宏CPU_TS_INIT_IN_DELAY_FUNCTION
//最大延时值为60秒
void CPU_TS_Tmr_Delay_US(uint32_t us);
#define CPU_TS_Tmr_Delay_MS(ms)     CPU_TS_Tmr_Delay_US(ms*1000)
#define CPU_TS_Tmr_Delay_S(s)       CPU_TS_Tmr_Delay_MS(s*1000)


#endif /* __CORE_DELAY_H */
