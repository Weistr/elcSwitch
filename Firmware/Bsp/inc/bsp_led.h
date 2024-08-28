#ifndef _BSP_LED_H
#define _BSP_LED_H
#include "main.h"
#include "stdbool.h"
#define LEDtotalNumber 2

#define  LED0ID 0
#define LED1ID 1

#define LEDconstOFF 0
#define LEDconstON 1
#define LEDblinkONE 2
#define LEDblinkWithCycle 3
void led_sta_update_20ms(void);
extern uint8_t LED_MODE[];
void LED_ONOFF(uint8_t ledn, bool sta);

#endif
