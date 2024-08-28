#include "bsp_flash.h"
#include "stm32f0xx_hal_flash.h"


//读取指定地址的半字(16位数据)
//也是按照半字读出，即每次读2个字节数据返回
uint16_t FLASH_ReadHalfWord(uint32_t address)
{   
	return *(__IO uint16_t*)address; 
}
void bsp_FlashPageErase(uint32_t PageAddress)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = PageAddress;//目标page所在空间首地址
	EraseInitStruct.NbPages = 1;
	uint32_t PageError=0;
	while(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK);
	
}

//要保存的数据

extern uint16_t laserTrigWidth;
extern uint16_t camTrigWidth;
extern int16_t camTrigPhase;
extern uint16_t pulseFrqMod;
void sysParmSave()
{
	uint32_t ubase = userFlashBase;
	
	HAL_FLASH_Unlock();
	bsp_FlashPageErase(ubase);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,ubase,0xAAAA);
	ubase += 2;
	HAL_FLASH_Lock();
}

void sysParmReadFlash()
{
		uint32_t ubase = userFlashBase;
	if(FLASH_ReadHalfWord(userFlashBase) != 0xAAAA)
	{//第一次读写
		sysParmSave();

	}
	else
	{
		ubase += 2;
		laserTrigWidth = FLASH_ReadHalfWord(ubase);
		ubase += 2;
		camTrigWidth = FLASH_ReadHalfWord(ubase);
		ubase += 2;
		camTrigPhase = FLASH_ReadHalfWord(ubase);
		ubase += 2;
		pulseFrqMod = FLASH_ReadHalfWord(ubase);		
	}

}














