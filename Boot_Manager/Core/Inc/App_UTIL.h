
#ifndef INC_APP_UTIL_H_
#define INC_APP_UTIL_H_

#include "stm32f4xx_hal.h"

#define FAILED 1
#define SUCCEEDED 0

void jump_to_application(uint32_t start_addr);
uint8_t * CalculateDigest(const uint8_t* image_start_address , uint32_t image_size );
uint8_t DigestCompare ( uint8_t *Digest , uint8_t *MetaDigest);

#endif /* INC_APP_UTIL_H_ */
