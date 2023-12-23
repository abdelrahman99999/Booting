#ifndef INC_APP_UTIL_H_
#define INC_APP_UTIL_H_

#include "main.h"
#include "rtc.h"
#include "usart.h"


#define APP_ENTER 0
#define BOOTLOADER_ENTER 1

extern uint8_t RX_BUFFER[2];

void App_Logic();

#endif /* INC_APP_UTIL_H_ */
