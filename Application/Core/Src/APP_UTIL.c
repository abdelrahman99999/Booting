
#include "APP_UTIL.h"


uint8_t RX_BUFFER[2];
uint8_t receive_flag =0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	receive_flag =99;
}


static void Write_RTC_backup_reg(uint32_t reg ,uint32_t data){
    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&hrtc, reg, data);
    HAL_PWR_DisableBkUpAccess();

}

static void Leaving_App_Handler(){
	//make bootManager enter bootloader
	Write_RTC_backup_reg(APPLICATION_ENTER_FLAG_ADDRESS,N_ENTER);
	Write_RTC_backup_reg(BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS,N_ENTER);
	//sw reset
	NVIC_SystemReset();
}


void App_Logic(){
	//LD1:GREEN
	//LD2:BLUE
	//LD3:RED
	 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin,GPIO_PIN_SET);
	 HAL_Delay(500);
	 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin,GPIO_PIN_RESET);
	 HAL_Delay(500);

	 if(receive_flag ==99){

		 	  receive_flag = 0;
			  if((RX_BUFFER[0]==0x01) && (RX_BUFFER[1]==0x05) ){
				  Leaving_App_Handler();
			 }

			 HAL_UART_Receive_IT(&huart4, RX_BUFFER, 2);
	}
}




