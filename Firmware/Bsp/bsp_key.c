#include "bsp_key.h"

//========================================================================
// ����: bsp_keyScan_20ms 
// ����: .
// ����: None.
// ����: None.
//========================================================================
bool key0Val=0;//����������1���ɿ���0

bool key0OneClicFlag=0;//����������־λ  ����ȡ��
bool key0TwoClicFlag=0;//����˫����־λ  ����ȡ��
bool key0LonClicFlag=0;//����������־λ  ����ȡ��
uint8_t clicTimeSpan_x20ms = 500/20;//˫��ʱ���� Ĭ��500ms
uint8_t long_push_x20ms = 1500/20;//����1500ms
uint8_t clicCnt=0;
void bsp_keyScan_20ms()
{
	#define keyPushed_val 0//��������Ϊ0

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
	
	
	if((key0ValPrevious != key0Val) && (key0Val != keyPushed_val) && (keyPushedFlag == 0))//�������º��ɿ�
	{
		clicCnt++;
		timeOutCnt=0;
		key0OneClicFlag = !key0OneClicFlag;//����
		if(clicCnt % 2 == 0)//˫��
			key0TwoClicFlag =! key0TwoClicFlag;
		if(clicCnt % 3 == 0)//����
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

