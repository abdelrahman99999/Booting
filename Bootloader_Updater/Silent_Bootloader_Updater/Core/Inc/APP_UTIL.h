/******************************************************************************
 *
 * File Name: APP_UTIL.h For Silent Bootloader Updater
 *
 * Description: header file for helpful functions and global variables used by Bootloader Updater
 *
 * Author: Abdelrahman Elsayed
 *
 *******************************************************************************/
#ifndef INC_APP_UTIL_H_
#define INC_APP_UTIL_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BOOTLOADER_START_ADDRESS 0x08040000
#define BOOTLOADER_BINARY_START_ADDRESS BOOTLOADER_START_ADDRESS

#define N_ENTER 0
#define ENTER 1
#define APPLICATION_ENTER_FLAG_ADDRESS 0x00
#define BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS (APPLICATION_ENTER_FLAG_ADDRESS+0x01)

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Update_Logic();

#endif /* INC_APP_UTIL_H_ */
