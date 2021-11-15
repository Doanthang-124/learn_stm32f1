#include "stm32f10x.h"                  // Device header

typedef enum {
	Flash_complete = 0,
	Flash_error
}Flash_status;

void Flash_unlock(void);
void Flash_erase(uint32_t u32Address);
Flash_status Write_flash(uint32_t u32AdressStart, uint16_t* u16Data, uint8_t u8Length);
Flash_status Read_flash( uint32_t u32AdressStart, uint16_t* u32Buffer, uint8_t u8Length);
void Flash_unlock(void)
{
	FLASH->KEYR = (uint32_t)0x45670123;
	FLASH->KEYR = (uint32_t)0xCDEF89AB;
}
void Flash_erase(uint32_t u32Address)
{
	/* check no operation ongoing - BSY*/
	while(FLASH->SR &FLASH_SR_BSY);
	/* read Flash lock or not ang unlock if necessary*/
	if(FLASH->CR == FLASH_CR_LOCK)
	{
		Flash_unlock();
	}
	/*set FLASH_CR_PER to 1*/
	FLASH->CR |= FLASH_CR_PER;
	/* Write into flash address*/
	FLASH->AR = u32Address; 
	/*set FLASH_CR_STRT to 1*/
	FLASH->CR |= FLASH_CR_STRT;
	/* wait to complete*/
	while(FLASH->SR &FLASH_SR_BSY);
	/*set FLASH_CR_PER to 0*/
	FLASH->CR &= ~FLASH_CR_PER;
	/*set FLASH_CR_STRT to 0*/
	FLASH->CR &= ~FLASH_CR_STRT;
}
Flash_status Write_flash( uint32_t u32AdressStart, uint16_t* u16Data, uint8_t u8Length)
{	
	while(FLASH->SR &FLASH_SR_BSY);
	/* read Flash lock or not ang unlock if necessary*/
	if(FLASH->CR == FLASH_CR_LOCK)
	{
		Flash_unlock();
	}
	if((u32AdressStart==0)||(u8Length%2 != 0))
	{
		return Flash_error;
	}
	/*set FLASH_PG_ to 1*/
	FLASH->CR |= FLASH_CR_PG;
	/* Write into flash address*/
	for(uint8_t u8Count = 0; u8Count < (u8Length/2);u8Count++)
	{
		*((uint16_t*)(u32AdressStart + u8Count*2))= *((uint16_t*)(u16Data + u8Count*2));
	}
	/* wait to complete*/
	while(FLASH->SR &FLASH_SR_BSY);
	/*reset FLASH_CR_PER to 0*/
	FLASH->CR &= ~FLASH_CR_PG;
	return Flash_complete;

}
Flash_status Read_flash( uint32_t u32AdressStart, uint16_t* u32Buffer, uint8_t u8Length)
{	
	while(FLASH->SR &FLASH_SR_BSY);
	/* read Flash lock or not ang unlock if necessary*/
	if(FLASH->CR == FLASH_CR_LOCK)
	{
		Flash_unlock();
	}
	if((u32AdressStart==0)||(u8Length%2 != 0))
	{
		return Flash_error;
	}
	/* Write into flash address*/
	for(uint8_t u8Count = 0; u8Count < (u8Length/2);u8Count++)
	{
		*((uint16_t*)(u32Buffer + u8Count*2))= *((uint16_t*)(u32AdressStart + u8Count*2));
	}
	/* wait to complete*/
	while(FLASH->SR &FLASH_SR_BSY);
	return Flash_complete;
}
int main()
{
	uint16_t data = 1234;
	uint16_t* bufferT = &data;
	uint16_t* bufferR;
	Flash_erase((uint32_t)0x08001000);
	Write_flash((uint32_t)0x08001000, bufferT, 2);
	Read_flash((uint32_t)0x08001000,bufferR,2);
	while(1)
	{
	}
	
	
	
}


