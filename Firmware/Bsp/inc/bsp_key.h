#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#include "main.h"
#include "stdbool.h"

void bsp_keyScan_20ms(void);
extern bool key0Val;//����������1���ɿ���0

extern bool key0OneClicFlag;//����������־λ  ����ȡ��
extern bool key0TwoClicFlag;//����˫����־λ  ����ȡ��
extern bool key0LonClicFlag;//����������־λ  ������1
extern uint8_t clicTimeSpan_x20ms;//˫��ʱ���� Ĭ��500ms
extern uint8_t long_push_x20ms;//����1000ms

#endif
