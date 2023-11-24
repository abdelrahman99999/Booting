
#include"App_UTIL.h"
#include "wolfssl/ssl.h"
void jump_to_application(uint32_t start_addr){

	/* Set the main stack pointer to to the application start address */
	__set_MSP(*(uint32_t *)start_addr);
	//__set_PSP(*(uint32_t *)start_addr);

	/* Get the main application start address */
	uint32_t jump_address = *(uint32_t *)(start_addr + 4);

	// Create function pointer for the main application
	void (*app_ptr)(void);
	app_ptr = (void *)(jump_address);

	// Now jump to the main application
	app_ptr();
}

/******************************************************************************/
/* \Description:
 * function to calculate the hash using SHA256 algorithm given the size
 * and the data to be hashed                                                  */
/******************************************************************************/
uint8_t * CalculateDigest(const uint8_t* image_start_address , uint32_t image_size ){
	/* Variables Declaration */
	wc_Sha256 sha256;
	static uint8_t hash[WC_SHA256_DIGEST_SIZE];  //Hash value

	int ret = -1;

	//Initialization of SHA256
	ret = wc_InitSha256(&sha256);
	if (ret != 0)
	{
		printf("Failed to initialize SHA structure\n");
	}

	//calculate digest API
	ret = wc_Sha256Update(&sha256, image_start_address , image_size);
	if (ret != 0){
		printf("Failed to calculate the hash\n");
	}else if (ret == 0){
		ret =  wc_Sha256Final(&sha256, hash);
	}

	if (ret != 0){
		printf("ERROR: Hash operation failed");
	}else
	{
		/*
		 * Do nothing
		 */
	}
	return hash;
}
/******************************************************************************/
/* \Description:
 * function to compare two digest values                                      */
/******************************************************************************/
uint8_t DigestCompare ( uint8_t *Digest , uint8_t *MetaDigest){
	int ret = 0;
	ret = memcmp(Digest,MetaDigest,32);
	if(ret== 0){
		ret = SUCCEEDED;
	}else{
		ret = FAILED;
	}
	return ret;
}
