/******************************************************************************
 *
 * File Name: APP_UTIL.c
 *
 * Description: Source file for helpful functions and global variables used by application
 *
 * Author: Abdelrahman Elsayed
 *
 *******************************************************************************/


/*******************************************************************************
 *                              Includes                       					*
 *******************************************************************************/
#include"App_UTIL.h"
#include "wolfssl/ssl.h"
#include "rtc.h"


/*******************************************************************************
 *                      Static Functions Definitions                            *
 *******************************************************************************/

/* Jump to specific Address */
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

/* calculate the hash using SHA256 algorithm given the size and the data to be hashed */
static uint8_t * CalculateDigest(const uint8_t* image_start_address , uint32_t image_size ){
	/* Variables Declaration */
	wc_Sha256 sha256;
	static uint8_t hash[WC_SHA256_DIGEST_SIZE];  //Hash value

	int ret = -1;

	//Initialization of SHA256
	ret = wc_InitSha256(&sha256);
	if (ret != 0)
	{
		printf("Failed to initialize SHA structure\n");
	}

	//calculate digest API
	ret = wc_Sha256Update(&sha256, image_start_address , image_size);
	if (ret != 0){
		printf("Failed to calculate the hash\n");
	}else if (ret == 0){
		ret =  wc_Sha256Final(&sha256, hash);
	}

	if (ret != 0){
		printf("ERROR: Hash operation failed");
	}else
	{
		/*
		 * Do nothing
		 */
	}
	return hash;
}

/* compare two digest values */
static uint8_t DigestCompare ( uint8_t *Digest , uint8_t *MetaDigest){
	int ret = 0;
	ret = memcmp(Digest,MetaDigest,32);
	if(ret== 0){
		ret = SUCCEEDED;
	}else{
		ret = FAILED;
	}
	return ret;
}

static uint8_t Read_RTC_backup_reg(uint8_t reg) {
    return (uint8_t)HAL_RTCEx_BKUPRead(&hrtc, reg);
}

static void Write_RTC_backup_reg(uint32_t reg ,uint32_t data){
    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&hrtc, reg, data);
    HAL_PWR_DisableBkUpAccess();

}


/*******************************************************************************
 *                      Global Functions Definitions                            *
 *******************************************************************************/

/***************************************************************************************************
 * [Function Name]: App_Logic
 *
 * [Description]:  App logic and behaviour
 *
 * [Args]:         void
 *
 * [Returns]:      void
 *
 ***************************************************************************************************/
void App_Logic(){

	//Toggling led
	for (uint8_t var = 0; var < 3; ++ var) {
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_RESET);
		HAL_Delay(200);
	}

	/*
	 * calculate Application Integrity
	 */
	uint32_t app_no_bytes = atoi( (uint8_t *)(APP_NO_OF_BYTES_START_ADDRESS) );
	uint8_t * digest_value_from_memory = (APP_Digest_START_ADDRESS);
	uint8_t * digest_value_calculated =CalculateDigest(APP_BINARY_START_ADDRESS, app_no_bytes);
	uint8_t Application_Integrity_result =DigestCompare(digest_value_from_memory,digest_value_calculated);

	/*
	 * reading Control Flags
	 */
	uint8_t Application_Enter_flag = Read_RTC_backup_reg(APPLICATION_ENTER_FLAG_ADDRESS);
	uint8_t BL_Updater_Enter_flag = Read_RTC_backup_reg(BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS);

	/*
	 * Branching Conditions
	 */
	if((Application_Integrity_result==SUCCEEDED )&&(Application_Enter_flag ==ENTER )){
		//jump to Application
		jump_to_Image_Address(APP_BINARY_START_ADDRESS);
	}else if(BL_Updater_Enter_flag == ENTER)
		//jump to BL Updater
		jump_to_Image_Address(BOOTLOADER_UPDATER_BINARY_START_ADDRESS);
	else{

		//reseting flags as for example(application flag = ENTER but its integrity is NOK)
		Write_RTC_backup_reg(APPLICATION_ENTER_FLAG_ADDRESS, N_ENTER);
		Write_RTC_backup_reg(BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS, N_ENTER);
		//jump to Bootloader
		jump_to_Image_Address(BOOTLOADER_BINARY_START_ADDRESS);
	}

}
