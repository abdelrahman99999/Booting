#ifndef INC_APP_UTIL_H_
#define INC_APP_UTIL_H_

#include "main.h"
#include "rtc.h"
#include "usart.h"

#define N_ENTER 0
#define ENTER 1

#define APPLICATION_ENTER_FLAG_ADDRESS 0x00
#define BOOTLOADER_UPDATER_ENTER_FLAG_ADDRESS (APPLICATION_ENTER_FLAG_ADDRESS+0x01)

extern uint8_t RX_BUFFER[2];

void App_Logic();

#endif /* INC_APP_UTIL_H_ */
