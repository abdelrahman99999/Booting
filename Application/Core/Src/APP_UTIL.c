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
#include "APP_UTIL.h"

/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/
/*
 * Buufer used to receive data from BCM
 */
uint8_t RX_BUFFER[2];

/*******************************************************************************
 *                              Static Global Variables                         *
 *******************************************************************************/
/*
 * flag for Receiving Indication
 */
static uint8_t receive_flag =0;


/*******************************************************************************
 *                              Call Backs                                      *
 *******************************************************************************/
/*
 * Uart Callback
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	receive_flag =99;
}


/*******************************************************************************
 *                      Static Functions Definitions                            *
 *******************************************************************************/
static void Write_RTC_backup_reg(uint32_t reg ,uint32_t data){
    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&hrtc, reg, data);
    HAL_PWR_DisableBkUpAccess();

}

/*
 * Handle leaving Application
 */
static void Leaving_App_Handler(){
	//make bootManager enter bootloader
	Write_RTC_backup_reg(APPLICATION_ENTER_FLAG_ADDRESS,N_ENTER);
	Write_RTC_backup_reg(BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS,N_ENTER);
	//sw reset
	NVIC_SystemReset();
}

/*******************************************************************************
 *                      Global Functions Definitions                           *
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
void App_Logic(void){
	//LD1:GREEN
	//LD2:BLUE
	//LD3:RED
	/*
	 * Toggling led
	 */
	 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin,GPIO_PIN_SET);
	 HAL_Delay(500);
	 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin,GPIO_PIN_RESET);
	 HAL_Delay(500);

	 /*
	  * if Receiving some data on uart
	  */
	 if(receive_flag ==99){
		 	 //reseting flag to use it next times
		 	  receive_flag = 0;
		 	  /*
		 	   * if the received data is leaving Application Command
		 	   */
			  if((RX_BUFFER[0]==0x01) && (RX_BUFFER[1]==0x05) ){
				  Leaving_App_Handler();
			 }

			  /*
			   * to receive data if the received data is not leaving Application Command
			   */
			 HAL_UART_Receive_IT(&huart4, RX_BUFFER, 2);
	}
}




