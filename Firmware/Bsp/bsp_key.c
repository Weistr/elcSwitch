#include "bsp_key.h"

//========================================================================
// 函数: bsp_keyScan_20ms 
// 描述: .
// 参数: None.
// 返回: None.
//========================================================================
bool key0Val=0;//按键按下置1，松开置0

bool key0OneClicFlag=0;//按键单击标志位  触发取反
bool key0TwoClicFlag=0;//按键双击标志位  触发取反
bool key0LonClicFlag=0;//按键长按标志位  触发取反
uint8_t clicTimeSpan_x20ms = 500/20;//双击时间间隔 默认500ms
uint8_t long_push_x20ms = 1500/20;//长按1500ms
uint8_t clicCnt=0;
void bsp_keyScan_20ms()
{
	#define keyPushed_val 0//按键按下为0

	static bool key0ValPrevious = !keyPushed_val;
	static uint8_t timeOutCnt=0,push_time_x20ms=0;
	key0Val = HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin);
	
	static bool keyPushedFlag = 0;
	
	
	
	if(key0Val == keyPushed_val)
	{
		push_time_x20ms++;
		if((push_time_x20ms > long_push_x20ms)&&(keyPushedFlag == 0))
		{
			push_time_x20ms = 0;
			keyPushedFlag = 1;
			key0LonClicFlag = !key0LonClicFlag;
		}
	}
	else
	{
		push_time_x20ms=0;
		if(keyPushedFlag == 1)
		{
			keyPushedFlag = 0;
			key0ValPrevious = key0Val;	
		}
	}
	
	
	if((key0ValPrevious != key0Val) && (key0Val != keyPushed_val) && (keyPushedFlag == 0))//按键按下后松开
	{
		clicCnt++;
		timeOutCnt=0;
		key0OneClicFlag = !key0OneClicFlag;//单击
		if(clicCnt % 2 == 0)//双击
			key0TwoClicFlag =! key0TwoClicFlag;
		if(clicCnt % 3 == 0)//三击
		{}
	}
	else
	{
		timeOutCnt++;
		if(timeOutCnt > clicTimeSpan_x20ms)
		{
			timeOutCnt = 0;
			clicCnt = 0;
		}
	}
	
	key0ValPrevious = key0Val;	

}

