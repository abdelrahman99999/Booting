/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
#include "fatfs_sd.h"
#define JANPATCH_STREAM     FIL
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0
#include "janpatch.h"
#include "App_UTIL.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

uint8_t app_size[8];

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t  data_received[100000];
uint8_t Complete_Receiving_flag=ERROR;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	if(flag ==ERROR){
		flag =SUCCESS;
	}

}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FATFS_Init();
  MX_SPI1_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  for(int i=0;i<3;i++){
	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_SET);
	  HAL_Delay(200);
	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_RESET);
	  HAL_Delay(200);
  }

//  //some variables for FatFs
//     FATFS FatFs; 	//Fatfs handle
//     FIL fil_old; 		//File handle
//     FIL fil_patch; 		//File handle
//     FIL fil_new; 		//File handle
//     FRESULT fres; //Result after operations
//
//     //Open the file system
//       fres = f_mount(&FatFs, "", 1); //1=mount now
//       if (fres != FR_OK) {
//     	  printf("error\n");
//       }
//
//       //Now let's try to open file "old.txt"
//         fres = f_open(&fil_old, "app.bin", FA_READ);
//         if (fres != FR_OK) {
//       	  printf("error\n");
//         }
//     //Now let's try to open file "patch.txt"
//  	  fres = f_open(&fil_patch, "diff.patch", FA_READ);
//  	  if (fres != FR_OK) {
//  		  printf("error\n");
//  	  }
//  	  //Now let's try to open file "new.txt"
//  	 fres = f_open(&fil_new, "reconstruct.bin", FA_WRITE| FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
//  	 if (fres != FR_OK) {
//  		 printf("error\n");
//  	 }
//      // janpatch_ctx contains buffers, and references to the file system functions
//      janpatch_ctx ctx = {
//          { (unsigned char*)malloc(1024), 1024 }, // source buffer
//          { (unsigned char*)malloc(1024), 1024 }, // patch buffer
//          { (unsigned char*)malloc(1024), 1024 }, // target buffer
//          &f_read,
//          &f_write,
//          &f_lseek
//      };
//
//    //patching
//    int res = janpatch(ctx, &fil_old, &fil_patch, &fil_new);
//
//    fres = f_close(&fil_old);
//    fres = f_close(&fil_patch);
//    fres = f_close(&fil_new);
//    //successful patching
//
//    if(res == 0){
//  	    char buffer[4];
//  	    int size;
//  	    fres = f_open(&fil_new, "reconstruct.bin", FA_READ);
//  	    // Reads line by line until the end
//  	    do
//  	    {
//  	       f_read(&fil_new, buffer, sizeof(buffer), &size);
//  	      // buffer now has the data ,can use and flash it
//  	      memset(buffer,0,sizeof(buffer));
//  	    }while(size !=0);
//    }
//
//    //don't forget to close your file!
//    fres = f_close(&fil_new);
//    //We're done, so de-mount the drive
//    fres =f_mount(NULL, "", 0);

  //blocking until receive the app size
  HAL_UART_Receive(&huart4, app_size, 8,HAL_MAX_DELAY);
  uint32_t app_size_length = atoi(app_size);
  HAL_UART_Receive_IT(&huart4, data_received, app_size_length);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int result =0;

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  if(flag ==SUCCESS){
		  flag =ERROR;
		  result = Flash_Memory_Erase(0x8060000, app_size_length);
		  result = Flash_Memory_Write(0x8060000, (uint32_t *)data_received, app_size_length);
		  jump_to_application(0x8060000);
	  }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
