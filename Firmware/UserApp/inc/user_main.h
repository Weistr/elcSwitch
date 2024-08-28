#ifndef _USER_MAIN_H
#define _USER_MAIN_H
#include "main.h"
#include <stdbool.h>
typedef struct 
{
	uint8_t Run;               //����״̬��Run/Stop
	uint16_t TIMCount;         //��ʱ������
	uint16_t TRITime;          //���ؼ�����
	void (*TaskHook) (void); //������
} TASK_COMPONENTS;       

//========================================================================
//                             �ⲿ�����ͱ�������
//========================================================================

void Task_Marks_Handler_Callback(void);
void Task_Pro_Handler_Callback(void);
void user_main(void);


#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

#endif
