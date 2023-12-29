/******************************************************************************
 *
 * File Name: APP_UTIL.h For Boot Manager
 *
 * Description: header file for helpful functions and global variables used by Boot Manager
 *
 * Author: Abdelrahman Elsayed
 *
 *******************************************************************************/
#ifndef INC_APP_UTIL_H_
#define INC_APP_UTIL_H_

/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/
#include "stm32f4xx_hal.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define FAILED 1
#define SUCCEEDED 0

#define N_ENTER 0
#define ENTER 1

#define APPLICATION_ENTER_FLAG_ADDRESS 0x00
#define BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS (APPLICATION_ENTER_FLAG_ADDRESS+0x01)

//Images Addresses
#define BOOTLOADER_START_ADDRESS 0x08040000
#define BOOTLOADER_BINARY_START_ADDRESS BOOTLOADER_START_ADDRESS

#define APP_START_ADDRESS 0x080A0000
#define APP_NO_OF_BYTES_START_ADDRESS APP_START_ADDRESS
#define APP_Digest_START_ADDRESS (APP_START_ADDRESS + 32)
#define APP_BINARY_START_ADDRESS (APP_START_ADDRESS + 0x200)

#define BOOTLOADER_UPDATER_START_ADDRESS 0x080A0000
#define BOOTLOADER_UPDATER_BINARY_START_ADDRESS BOOTLOADER_UPDATER_START_ADDRESS

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void App_Logic();

#endif /* INC_APP_UTIL_H_ */
