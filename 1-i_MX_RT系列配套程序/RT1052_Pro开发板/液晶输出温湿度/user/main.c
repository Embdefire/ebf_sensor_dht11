/**
  ******************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   dht11 温湿度传感器实验
  ******************************************************************
  * @attention
  *
  * 实验平台:野火  i.MXRT1052开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************
  */
#include "fsl_debug_console.h"
#include "fsl_elcdif.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "./delay/core_delay.h"   
#include "./systick/bsp_systick.h"
#include "./dht11/bsp_dht11.h"
#include "./lcd/bsp_lcd.h" 
#include "stdio.h" 
/*******************************************************************
 * Prototypes
 *******************************************************************/
DHT11_Data_TypeDef DHT11_Data;
/* 显示缓冲区 */
uint8_t dis_buf[1024];
/*******************************************************************
 * Code
 *******************************************************************/

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    /* 初始化内存保护单元 */
    BOARD_ConfigMPU();
    /* 初始化开发板引脚 */
    BOARD_InitPins();
    /* 初始化开发板时钟 */
    BOARD_BootClockRUN();
    /* 初始化调试串口 */
    BOARD_InitDebugConsole();
	  /* 初始化精确延时*/
		CPU_TS_TmrInit();
		/* 初始化滴答定时器 */
		SysTick_Init();
    /* 打印系统时钟 */
    PRINTF("\r\n");
    PRINTF("*****欢迎使用 野火i.MX RT1052 开发板*****\r\n");
    PRINTF("CPU:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_CpuClk));
    PRINTF("AHB:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_AhbClk));
    PRINTF("SEMC:            %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SemcClk));
    PRINTF("SYSPLL:          %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllClk));
    PRINTF("SYSPLLPFD0:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
    PRINTF("SYSPLLPFD1:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
    PRINTF("SYSPLLPFD2:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
    PRINTF("SYSPLLPFD3:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));  
		PRINTF("\r\n*** dht11 温湿度传感器实验***\r\n");
		/* 初始化LCD */
    LCD_Init(LCD_INTERRUPT_ENABLE);
		/* DHT11初始化 */
		DHT11_GPIO_Config();
		LCD_DisplayStringLine(LINE(1),(uint8_t* )"DHT11 temperature & humidity detect demo");
    while(1)
    {
				/*调用DHT11_Read_TempAndHumidity读取温湿度，若成功则输出该信息*/
				if( Read_DHT11 ( & DHT11_Data ) == SUCCESS)
				{
						PRINTF("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n",\
						DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
						LCD_ClearLine(LINE(2));
						LCD_ClearLine(LINE(3));
						sprintf((char*)dis_buf,"humidity: %2d.%2d %%RH ",DHT11_Data.humi_int,DHT11_Data.humi_deci);
						LCD_DisplayStringLine(LINE(4),dis_buf);

						sprintf((char*)dis_buf,"temperature: %2d.%2d degree Celsius ",DHT11_Data.temp_int,DHT11_Data.temp_deci);
						LCD_DisplayStringLine(LINE(5),dis_buf);
				}		
				else
				{
						PRINTF("Read DHT11 ERROR!\r\n");     
						LCD_SetTextColor(CL_RED);
						LCD_DisplayStringLine(LINE(2),(uint8_t* )"DHT11 initialization failed!");
						LCD_DisplayStringLine(LINE(3),(uint8_t* )"Please check the connection!");	
				}
				Delay_ms(2000);
    }     

}
/****************************END OF FILE**********************/
