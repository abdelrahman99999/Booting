
#include"App_UTIL.h"
#include "usart.h"
#include "rtc.h"

static uint8_t Bootloader_Rx_Buffer[BOOTLOADER_RX_BUFFER_LENGTH];

static enum Bootloader_Supported_Commands{
	BOOTLOADER_GET_VERION_COMMAND,
	BOOTLOADER_MEM_WRITE_APP_COMMAND,
	BOOTLOADER_MEM_ERASE_APP_COMMAND,
	BOOTLOADER_LEAVING_TO_BOOT_MANAGER_COMMAND,
	BOOTLOADER_MEM_WRITE_BOOTLOADER_UPDATER_COMMAND,
	BOOTLOADER_MEM_ERASE_BOOTLOADER_UPDATER_COMMAND,
	BOOTLOADER_LEAVING_TO_BOOTLOADER_UPDATER_COMMAND

};

static void Write_RTC_backup_reg(uint32_t reg ,uint32_t data){
    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&hrtc, reg, data);
    HAL_PWR_DisableBkUpAccess();

}

static void jump_to_Image_Address(uint32_t start_addr){

	/* Set the main stack pointer to to the application start address */
	__set_MSP(*(uint32_t *)start_addr);
	//__set_PSP(*(uint32_t *)start_addr);

	/* Get the main application start address */
	uint32_t jump_address = *(uint32_t *)(start_addr + 4);

	// Create function pointer for the main application
	void (*app_ptr)(void);
	app_ptr = (void *)(jump_address);

	// Now jump to the main application
	app_ptr();
}

static uint32_t GetSector(uint32_t Address)
{
	uint32_t sector = 0;

	/* BANK 1 */
	if((Address >= 0x08000000 ) && (Address < 0x08003FFF))
	{
		sector = FLASH_SECTOR_0;
	}

	else if((Address >= 0x08004000 ) && (Address <  0x08007FFF))
	{
		sector = FLASH_SECTOR_1;
	}

	else if((Address >= 0x08008000) && (Address <  0x0800BFFF))
	{
		sector = FLASH_SECTOR_2;
	}

	else if((Address >= 0x0800C000) && (Address < 0x0800FFFF))
	{
		sector = FLASH_SECTOR_3;
	}

	else if((Address >=  0x08010000) && (Address <  0x0801FFFF))
	{
		sector = FLASH_SECTOR_4;
	}

	else if((Address >=  0x08020000) && (Address < 0x0803FFFF))
	{
		sector = FLASH_SECTOR_5;
	}

	else if((Address >= 0x08040000) && (Address < 0x0805FFFF))
	{
		sector = FLASH_SECTOR_6;
	}

	else if((Address >= 0x08060000) && (Address < 0x0807FFFF))
	{
		sector = FLASH_SECTOR_7;
	}

	else if((Address >= 0x08080000) && (Address < 0x0809FFFF))
	{
		sector = FLASH_SECTOR_8;
	}

	else if((Address >= 0x080A0000) && (Address < 0x080BFFFF))
	{
		sector = FLASH_SECTOR_9;
	}

	else if((Address >= 0x080C0000) && (Address < 0x080DFFFF))
	{
		sector = FLASH_SECTOR_10;
	}

	else if((Address >= 0x080E0000) && (Address < 0x080FFFFF))
	{
		sector = FLASH_SECTOR_11;
	}

	/* BANK 2 */
	if((Address >= 0x08100000 ) && (Address < 0x08103FFF))
	{
		sector = FLASH_SECTOR_12;
	}

	else if((Address >= 0x08104000 ) && (Address <  0x08107FFF))
	{
		sector = FLASH_SECTOR_13;
	}

	else if((Address >= 0x08108000) && (Address <  0x0810BFFF))
	{
		sector = FLASH_SECTOR_14;
	}

	else if((Address >= 0x0810C000) && (Address < 0x0810FFFF))
	{
		sector = FLASH_SECTOR_15;
	}

	else if((Address >=  0x08110000) && (Address <  0x0811FFFF))
	{
		sector = FLASH_SECTOR_16;
	}

	else if((Address >=  0x08120000) && (Address < 0x0813FFFF))
	{
		sector = FLASH_SECTOR_17;
	}

	else if((Address >= 0x08140000) && (Address < 0x0815FFFF))
	{
		sector = FLASH_SECTOR_18;
	}

	else if((Address >= 0x08160000) && (Address < 0x0817FFFF))
	{
		sector = FLASH_SECTOR_19;
	}

	else if((Address >= 0x08180000) && (Address < 0x0819FFFF))
	{
		sector = FLASH_SECTOR_20;
	}

	else if((Address >= 0x081A0000) && (Address < 0x081BFFFF))
	{
		sector = FLASH_SECTOR_21;
	}

	else if((Address >= 0x081C0000) && (Address < 0x081DFFFF))
	{
		sector = FLASH_SECTOR_22;
	}

	else if((Address >= 0x081E0000) && (Address < 0x081FFFFF))
	{
		sector = FLASH_SECTOR_23;
	}
	return sector;
}

static uint8_t Flash_Memory_Erase(uint32_t StartSectorAddress , uint32_t dataSizeInBytes){
	static FLASH_EraseInitTypeDef EraseInitStruct;   /* Structure to erase the flash area */
	uint32_t SECTORError;

	/* Getting the number of sector to erase from the first sector */
	uint32_t StartSector = GetSector(StartSectorAddress);                /*getting the start sector number*/
	uint32_t EndSectorAddress = StartSectorAddress + dataSizeInBytes;    /*getting the end sector address*/
	uint32_t EndSector = GetSector(EndSectorAddress);                    /*getting the end sector number*/

	/* Filling the erasing structure */
	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector        = StartSector;
	EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	/* Unlocking the Flash control register */
	HAL_FLASH_Unlock();

	/* check if the erasing process is done correctly */
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	{
		/*Error occurred while page erase*/
		return ERROR;
	}

	/* Locking the Flash control register */
	HAL_FLASH_Lock();

	return SUCCESS;
}

static uint8_t Flash_Memory_Write(uint32_t StartSectorAddress ,uint32_t *data, uint32_t dataSizeInBytes){
	uint32_t numofWords=dataSizeInBytes/4;     /*getting number of words to write*/
	uint32_t numofWordsWritten=0;

	/* Unlocking the Flash control register */
	HAL_FLASH_Unlock();

	/* looping on the data word by word to write it in the flash */
	while(numofWordsWritten < numofWords){

		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartSectorAddress, data[numofWordsWritten]) == HAL_OK)
		{
			StartSectorAddress += 4;
			numofWordsWritten++;
		}
		else
		{
			/* Error occurred while writing data in Flash memory*/
			return ERROR;
		}

	}

	/* Locking the Flash control register */
	HAL_FLASH_Lock();

	return SUCCESS;

}

static void Get_Vrsion_Command_Handler(){
	uint8_t bootloader_version[3]={BOOTLOADER_MAJOR_VERSION,BOOTLOADER_MINOR_VERSION,BOOTLOADER_PATCH_VERSION};
	HAL_UART_Transmit(&huart4, bootloader_version, 3, HAL_MAX_DELAY);
}

static void Mem_Erase_APP_Command_Handler(){
	uint32_t app_size_length = atoi(&Bootloader_Rx_Buffer[2]);

	uint8_t result = Flash_Memory_Erase(APP_START_ADDRESS ,app_size_length+0x200 );
	HAL_UART_Transmit(&huart4, &result, 1, HAL_MAX_DELAY);
}


static void Mem_Write_APP_Command_Handler(){
	uint32_t app_size_length = atoi(&Bootloader_Rx_Buffer[2]);

	HAL_UART_Receive(&huart4, &Bootloader_Rx_Buffer[42], app_size_length, HAL_MAX_DELAY);
	//writing app length
	uint8_t result = Flash_Memory_Write(APP_NO_OF_BYTES_START_ADDRESS, (uint32_t *)&Bootloader_Rx_Buffer[2], 8);
	//writing app digest
	result = Flash_Memory_Write(APP_Digest_START_ADDRESS, (uint32_t *)&Bootloader_Rx_Buffer[10], 32);
	//writing app itself
	result = Flash_Memory_Write(APP_BINARY_START_ADDRESS, (uint32_t *)&Bootloader_Rx_Buffer[42], app_size_length);


	HAL_UART_Transmit(&huart4, &result, 1, HAL_MAX_DELAY);
	//write on RTC reg no 0 to make bootManager enter application if other bootManager conditions are true
	Write_RTC_backup_reg(0x00, APP_ENTER);
}

static void Leaving_To_Boot_Manager_Command_Handler(){
	//sw reset
	NVIC_SystemReset();
}

static void Mem_Write_Bootloader_updater_Command_Handler(){

	uint32_t Bootloader_updater_size_length = atoi(&Bootloader_Rx_Buffer[2]);

	HAL_UART_Receive(&huart4, &Bootloader_Rx_Buffer[10], Bootloader_updater_size_length, HAL_MAX_DELAY);

	//writing  Bootloader updater binary
	uint8_t result = Flash_Memory_Write(BOOTLOADER_UPDATER_BINARY_START_ADDRESS, (uint32_t *)&Bootloader_Rx_Buffer[10], Bootloader_updater_size_length);

	HAL_UART_Transmit(&huart4, &result, 1, HAL_MAX_DELAY);


}

static void Mem_Erase_Bootloader_updater_Command_Handler(){
	uint32_t Bootloader_updater_size_length = atoi(&Bootloader_Rx_Buffer[2]);

	uint8_t result = Flash_Memory_Erase(BOOTLOADER_UPDATER_BINARY_START_ADDRESS ,Bootloader_updater_size_length );
	HAL_UART_Transmit(&huart4, &result, 1, HAL_MAX_DELAY);
}


static void Bootloader_Leaving_To_Bootloader_Updater_Command_Handler(){
	jump_to_Image_Address(BOOTLOADER_UPDATER_BINARY_START_ADDRESS);
}



void Bootloader_Receive_Command(void){
	uint8_t command_Length = 0;
	/*clear receiving buffer*/
	memset(Bootloader_Rx_Buffer, 0, BOOTLOADER_RX_BUFFER_LENGTH);
	/* Read the length of the command received from the BCM */
	HAL_UART_Receive(&huart4, Bootloader_Rx_Buffer, 1, HAL_MAX_DELAY);

	command_Length = Bootloader_Rx_Buffer[0];
	/* Read the command*/
	HAL_UART_Receive(&huart4, &Bootloader_Rx_Buffer[1], command_Length, HAL_MAX_DELAY);

	switch(Bootloader_Rx_Buffer[1]){
	case BOOTLOADER_GET_VERION_COMMAND:
		Get_Vrsion_Command_Handler();
		break;
	case BOOTLOADER_MEM_WRITE_APP_COMMAND:
		Mem_Write_APP_Command_Handler();
		break;
	case BOOTLOADER_MEM_ERASE_APP_COMMAND:
		Mem_Erase_APP_Command_Handler();
		break;
	case BOOTLOADER_LEAVING_TO_BOOT_MANAGER_COMMAND:
		Leaving_To_Boot_Manager_Command_Handler();
		break;
	case BOOTLOADER_MEM_WRITE_BOOTLOADER_UPDATER_COMMAND:
		Mem_Write_Bootloader_updater_Command_Handler();
		break;
	case BOOTLOADER_MEM_ERASE_BOOTLOADER_UPDATER_COMMAND:
		Mem_Erase_Bootloader_updater_Command_Handler();
		break;
	case BOOTLOADER_LEAVING_TO_BOOTLOADER_UPDATER_COMMAND:
		Bootloader_Leaving_To_Bootloader_Updater_Command_Handler();
		break;
	default:
		//do no thing
		break;
	}
}





