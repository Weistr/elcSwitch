#include "bsp_flash.h"
#include "stm32f0xx_hal_flash.h"


//��ȡָ����ַ�İ���(16λ����)
//Ҳ�ǰ��հ��ֶ�������ÿ�ζ�2���ֽ����ݷ���
uint16_t FLASH_ReadHalfWord(uint32_t address)
{   
	return *(__IO uint16_t*)address; 
}
void bsp_FlashPageErase(uint32_t PageAddress)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = PageAddress;//Ŀ��page���ڿռ��׵�ַ
	EraseInitStruct.NbPages = 1;
	uint32_t PageError=0;
	while(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK);
	
}

//Ҫ���������

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
	{//��һ�ζ�д
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














