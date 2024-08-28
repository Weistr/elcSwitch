#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "main.h"
#include "stdbool.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 	16 	 		//��ѡSTM32��FLASH������С(��λΪK)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //�ֽ�
#else 
#define STM_SECTOR_SIZE	2048
#endif	
//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 		//STM32 FLASH����ʼ��ַ
#define userFlashBase  0x08007800 //30KBλ��(30*1024 + STM32_FLASH_BASE)������2KB
void sysParmSave(void);
void sysParmReadFlash(void);
void bsp_FlashPageErase(uint32_t PageAddress);


uint16_t FLASH_ReadHalfWord(uint32_t address);

#define pulseFrqMod_readFromFlash() FLASH_ReadHalfWord(userFlashBase+8)

#endif

