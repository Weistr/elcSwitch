#include "usart.h"
#include "bsp_uart.h"
#include "user_main.h"
#include "bsp_led.h"
#include "string.h"
#include "bsp_delay.h"
//========================================================================
// 函数: 
// 描述: 串口相关.
// 参数: None.
// 返回: None.
//========================================================================

uint8_t uart2RxBuf[uart2MaxLen];
uint8_t uart2TxBuf[uart2MaxLen];
uint8_t uart2RxLen;
void uart_init()
{

	HAL_UARTEx_ReceiveToIdle_DMA(&huart2,uart2RxBuf,uart2MaxLen);
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);
	
}


//串口接收完成中断回调函数
extern void pulseOut_uartRcvTask(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART2)
	{
		HAL_UARTEx_ReceiveToIdle_DMA(huart, uart2RxBuf, uart2MaxLen);
		uart2RxLen = Size;
		pulseOut_uartRcvTask();
	}	
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

		MX_USART2_UART_Init();
		uart_init();
		delay_ms(20);
}
void uartPrintString(UART_HandleTypeDef *huart, char* str)
{
	if(huart->Instance == USART2)
	{
		memset(uart2TxBuf,0,uart2MaxLen);
		uint8_t i = 0;
		for (; (i < uart2MaxLen) && (str[i]!=0); i++)
		{
			uart2TxBuf[i]=str[i];
		}		
		HAL_UART_Transmit_DMA(huart,(uint8_t *)&uart2TxBuf[0], i);
	}

}









