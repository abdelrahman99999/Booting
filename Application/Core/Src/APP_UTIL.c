
#include "APP_UTIL.h"
#include "main.h"
#include "rtc.h"


static void Write_RTC_backup_reg(uint32_t reg ,uint32_t data){
    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&hrtc, reg, data);
    HAL_PWR_DisableBkUpAccess();

}
void App_Logic(){
	//LD1:GREEN
	//LD2:BLUE
	//LD3:RED
	 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin,GPIO_PIN_SET);
	 HAL_Delay(500);
	 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin,GPIO_PIN_RESET);
	 HAL_Delay(500);
}


void Leaving_App_Handler(){
	//write on flag to make bootManager enter bootloader
	Write_RTC_backup_reg(0x00,BOOTLOADER_ENTER);
	//sw reset
	NVIC_SystemReset();
}


