#include "pulseOut.h"
#include "tim.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_flash.h"
#include "bsp_uart.h"
#include "string.h"
#include "math.h"
#include "usart.h"

uint16_t pulseFrqMod = 0;
#define pulseStop 0
#define constON 1

/**
 * @brief 初始化PWM
*/

void pluseOutInit()
{
	__HAL_TIM_PRESCALER(&htim3,20);//1us
	__HAL_TIM_SetAutoreload(&htim3,1000);
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,1000);//高电平时间
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);//高电平时间		
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0);//高电平时间

	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
}




void pulseOut_task()
{
	static bool key0OneClicFlag_previous = 0; 
	static bool key0TwoClicFlag_previous = 0; 
	static bool key0LonClicFlag_previous = 0; 
	if (key0OneClicFlag_previous != key0OneClicFlag)//单击按键
	{
		key0OneClicFlag_previous = key0OneClicFlag;
		//单击按键想实现的功能
		if (key0OneClicFlag)
		{
			LED_MODE[LED0ID] = LEDconstON;
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);//高电平时间
		}
		else
		{
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,1000);//高电平时间
			LED_MODE[LED0ID] = LEDconstOFF;
		}
	}
	else if (key0LonClicFlag_previous != key0LonClicFlag)//按键长按
	{
		key0LonClicFlag_previous = key0LonClicFlag;
	}
	else if(key0TwoClicFlag_previous != key0TwoClicFlag)//双击按键
	{

	}
}




int32_t powi(int32_t x,int32_t y)
{
	if(y == 0)return 1;
	else if (y==1)return x;
	else
	{
		for (uint8_t i = 1; i < y; i++)
		{
			x = x*x;
		}
		return x;
	}
}
		uint16_t pulseToSet=0;
//串口接收
uint8_t uart_timeout_cnt = 0;
void pulseOut_uartRcvTask()
{

	uart_timeout_cnt = 0;
	if(strncmp("disable output",(char*)uart2RxBuf,sizeof("disable output")-1)==0)
	{
		pulseFrqMod = pulseStop;
		uartPrintString(&huart2,"\r\noutput disabled!");
	}
	else if(strncmp("constON",(char*)uart2RxBuf,sizeof("constON")-1)==0)
	{
		pulseFrqMod = constON;
		uartPrintString(&huart2,"\r\nok!");
	}
	else
	{
		uartPrintString(&huart2,(char*)uart2RxBuf);
	}
	
	memset(uart2RxBuf,0,uart2MaxLen);
}

void uart_timeOut()
{
	
	if(uart_timeout_cnt > 5)
	{
		uart_timeout_cnt=0;
		  //MX_USART1_UART_Init();

		//uart_init();
	}
	uart_timeout_cnt++;
}











