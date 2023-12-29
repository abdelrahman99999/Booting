/******************************************************************************
 *
 * File Name: APP_UTIL.h For Application
 *
 * Description: header file for helpful functions and global variables used by Application
 *
 * Author: Abdelrahman Elsayed
 *
 *******************************************************************************/
#ifndef INC_APP_UTIL_H_
#define INC_APP_UTIL_H_

/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "main.h"
#include "rtc.h"
#include "usart.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define N_ENTER 0
#define ENTER 1

#define APPLICATION_ENTER_FLAG_ADDRESS 0x00
#define BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS (APPLICATION_ENTER_FLAG_ADDRESS+0x01)


/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/

extern uint8_t RX_BUFFER[2];


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void App_Logic();

#endif /* INC_APP_UTIL_H_ */
