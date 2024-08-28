#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "main.h"
#include "stdbool.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
//用户根据自己的需要设置
#define STM32_FLASH_SIZE 	16 	 		//所选STM32的FLASH容量大小(单位为K)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //字节
#else 
#define STM_SECTOR_SIZE	2048
#endif	
//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 		//STM32 FLASH的起始地址
#define userFlashBase  0x08007800 //30KB位置(30*1024 + STM32_FLASH_BASE)，可用2KB
void sysParmSave(void);
void sysParmReadFlash(void);
void bsp_FlashPageErase(uint32_t PageAddress);


uint16_t FLASH_ReadHalfWord(uint32_t address);

#define pulseFrqMod_readFromFlash() FLASH_ReadHalfWord(userFlashBase+8)

#endif

