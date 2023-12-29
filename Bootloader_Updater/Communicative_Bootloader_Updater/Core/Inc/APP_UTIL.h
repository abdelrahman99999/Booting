/******************************************************************************
 *
 * File Name: APP_UTIL.h For Communicative Bootloader Updater
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
#define BOOTLOADER_UPDATER_RX_BUFFER_LENGTH     100000


#define BOOTLOADER_UPDATER_MAJOR_VERSION 7
#define BOOTLOADER_UPDATER_MINOR_VERSION 2
#define BOOTLOADER_UPDATER_PATCH_VERSION 9

#define BOOTLOADER_START_ADDRESS 0x08040000
#define BOOTLOADER_BINARY_START_ADDRESS BOOTLOADER_START_ADDRESS

#define N_ENTER 0
#define ENTER 1
#define APPLICATION_ENTER_FLAG_ADDRESS 0x00
#define BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS (APPLICATION_ENTER_FLAG_ADDRESS+0x01)

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void App_Logic(void);

#endif /* INC_APP_UTIL_H_ */
