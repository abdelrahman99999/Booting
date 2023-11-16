
#ifndef INC_APP_UTIL_H_
#define INC_APP_UTIL_H_

#include "stm32f4xx_hal.h"
uint32_t GetSector(uint32_t Address);

uint8_t Flash_Memory_Erase(uint32_t StartSectorAddress , uint32_t dataSizeInBytes);

uint8_t Flash_Memory_Write(uint32_t StartSectorAddress ,uint32_t *data, uint32_t dataSizeInBytes);

void jump_to_application(uint32_t start_addr);


#endif /* INC_APP_UTIL_H_ */
