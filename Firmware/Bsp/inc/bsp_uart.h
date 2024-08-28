#ifndef _BSP_UART_H
#define _BSP_UART_H
#include "main.h"


extern uint8_t uart2RxBuf[];
extern uint8_t uart2TxBuf[];
extern uint8_t uart2RxLen;
void uart_init(void);
void uartPrintString(UART_HandleTypeDef *huart, char* str);

#define uart2MaxLen 64

#endif
