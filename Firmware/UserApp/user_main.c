#include "stdbool.h"
#include "user_main.h"

#include "bsp_led.h"
#include "bsp_uart.h"
#include "bsp_flash.h"
#include "bsp_key.h"
#include "pulseOut.h"
/***************************************************/
/*********************TASK************************/
/***************************************************/
//========================================================================
// ����: basic  task
// ����: .
// ����: None.
// ����: None.
//========================================================================
	
void basicTask_entry()
{
	led_sta_update_20ms();	
	bsp_keyScan_20ms();
}
/***************************************************/
/*********************��ʼ��************************/
/***************************************************/

void user_main()
{
	sysParmReadFlash();
	uart_init();
	pluseOutInit();
	
}

void task1()
{
}
//========================================================================
//                         ���ر������� & �������
//========================================================================


extern void pulseOut_task(void);
extern void uart_timeOut(void);
static TASK_COMPONENTS Task_Comps[]=
{
//״̬  ����  ����  ����
	{0, 20, 20, basicTask_entry},				/* task 1 Period�� 2ms*/
	{0, 20, 20, pulseOut_task},				/* task 2 Period�� 100ms �ɿ�����*/
	{0, 100, 100, uart_timeOut},			/* task 3 Period�� 300ms ��ص�ѹ*/
//	{0, 20, 20, adc_scan},					/* task 4 Period�� 500ms */
//	{0, 500, 500, task_B},					/* task 5 Period�� 500ms */
//	{0, 500, 500, task_C},					/* task 6 Period�� 500ms */
//	{0, 500, 500, task_D},					/* task 7 Period�� 500ms */
//	{0, 500, 500, task_E},					/* task 8 Period�� 500ms */

	/* Add new task here */
};

uint8_t Tasks_Max = sizeof(Task_Comps)/sizeof(Task_Comps[0]);

//========================================================================
// ����: Task_Handler_Callback
// ����: �����ǻص�����.
// ����: None.
// ����: None.
//========================================================================
void Task_Marks_Handler_Callback(void)
{
	uint8_t i;
	for(i=0; i<Tasks_Max; i++)
	{
		if(Task_Comps[i].TIMCount)    /* If the time is not 0 */
		{
			Task_Comps[i].TIMCount--;  /* Time counter decrement */
			if(Task_Comps[i].TIMCount == 0)  /* If time arrives */
			{
				/*Resume the timer value and try again */
				Task_Comps[i].TIMCount = Task_Comps[i].TRITime;  
				Task_Comps[i].Run = 1;    /* The task can be run */
			}
		}
	}
}

//========================================================================
// ����: Task_Pro_Handler_Callback
// ����: ������ص�����.
// ����: None.
// ����: None.
//========================================================================
void Task_Pro_Handler_Callback(void)
{
	uint8_t i;
	for(i=0; i<Tasks_Max; i++)
	{
		if(Task_Comps[i].Run) /* If task can be run */
		{
			Task_Comps[i].Run = 0;    /* Flag clear 0 */
			Task_Comps[i].TaskHook();  /* Run task */
		}
	}
}






