#include "bsp_led.h"
#include "stdbool.h"
uint8_t LED_MODE[LEDtotalNumber];

void LED_ONOFF(uint8_t ledn, bool sta)
{
	switch(ledn)
	{
		case 0:
			if(sta)HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			if(sta)HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
			break;		
	}
}
void led_sta_update_20ms()
{
	static uint8_t led_cnt[LEDtotalNumber];
	static bool led_sta[LEDtotalNumber];//1: on 0:off
	for(uint8_t i=0; i<LEDtotalNumber; i++)
	{
		switch(LED_MODE[i])
		{
			case LEDconstOFF:
				LED_ONOFF(i,0);
				break;
			case LEDconstON:
				LED_ONOFF(i,1);
				break;
			case LEDblinkONE:
				led_cnt[i]++;
				if(led_cnt[i] > 25)
				{
					led_cnt[i] = 0;
					led_sta[i] = !led_sta[i];
				}
				LED_ONOFF(i,led_sta[i]);
				break;
			case LEDblinkWithCycle:
				led_sta[i] = !led_sta[i];
				LED_ONOFF(i,led_sta[i]);
				break;
		}
	}
}
