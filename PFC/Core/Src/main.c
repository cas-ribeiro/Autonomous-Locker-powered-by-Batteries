/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "lock.h"
#include "security.h"
#include "led.h"
#include "scanner.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */



/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define RXBUFFERSIZE 12
//#define TXBUFFERSIZE 12
#define TIMEOUT 10000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef UartHandle;
//static GPIO_InitTypeDef  GPIO_InitStruct;

/* USER CODE BEGIN PV */
/* Buffer used for transmission */



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
void SystemClock_Decrease(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
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


	GPIO_InitTypeDef  GPIO_InitStruct;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  SystemClock_Config();
  /* USER CODE BEGIN Init */

  //Button Initialization
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);



  //MX_USART1_UART_Init();

  Lock_Init(&LockerStruct);
  LED_Init();
  Scanner_Init(&UartHandle);
  LED_BlueTurnOn();
  Lock_ReadFromFlash(&LockerStruct);

//  GPIO_InitStruct.Pin = GPIO_PIN_3;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull  = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);



//Enable Wake Up Interrupt line

  NVIC_SetPriority((IRQn_Type)(EXTI0_IRQn), 0x03);
  HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI0_IRQn));
  __NVIC_EnableIRQ(EXTI0_IRQn);


  //Enable Locker Interrupts lines

  NVIC_SetPriority((IRQn_Type)(EXTI1_IRQn), 0x03);
  HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI1_IRQn));
  __NVIC_EnableIRQ(EXTI1_IRQn);

  NVIC_SetPriority((IRQn_Type)(EXTI3_IRQn), 0x03);
  HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI3_IRQn));
  __NVIC_EnableIRQ(EXTI3_IRQn);

  NVIC_SetPriority((IRQn_Type)(EXTI4_IRQn), 0x03);
  HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI4_IRQn));
  __NVIC_EnableIRQ(EXTI4_IRQn);

  NVIC_SetPriority((IRQn_Type)(EXTI9_5_IRQn), 0x03);
  HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI9_5_IRQn));
  __NVIC_EnableIRQ(EXTI9_5_IRQn);

  NVIC_SetPriority((IRQn_Type)(EXTI15_10_IRQn), 0x03);
  HAL_NVIC_EnableIRQ((IRQn_Type)(EXTI15_10_IRQn));
  __NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE END 2 */



  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {


	   while(!Scanner_Sleep(&UartHandle));

	    LED_BlueTurnOff();
	    SystemClock_Decrease();
	    HAL_SuspendTick();

	    HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);

        HAL_PWREx_DisableLowPowerRunMode();

        SystemClock_Config();
        HAL_ResumeTick();

        HAL_Delay(10);

      	if(HAL_GPIO_ReadPin(LockerStruct[0].Lock_Pin2.GPIOx, LockerStruct[0].Lock_Pin2.GPIO_Init.Pin) && (!LockerStruct[0].isVandalized)){
    			Lock_AddErrorLog (&LogsStruct[logsCount],LockerStruct[0].Lock_Pin1.GPIO_Init.Pin, LOCKER_VANDALIZED);
    			LockerStruct[0].isVandalized = 1;
      	}

      	if(HAL_GPIO_ReadPin(LockerStruct[1].Lock_Pin2.GPIOx, LockerStruct[1].Lock_Pin2.GPIO_Init.Pin) && (!LockerStruct[1].isVandalized)){
    			Lock_AddErrorLog (&LogsStruct[logsCount],LockerStruct[1].Lock_Pin1.GPIO_Init.Pin, LOCKER_VANDALIZED);
    			LockerStruct[1].isVandalized = 1;
      	}

      	if(HAL_GPIO_ReadPin(LockerStruct[2].Lock_Pin2.GPIOx, LockerStruct[2].Lock_Pin2.GPIO_Init.Pin) && (!LockerStruct[2].isVandalized)){
    			Lock_AddErrorLog (&LogsStruct[logsCount],LockerStruct[2].Lock_Pin1.GPIO_Init.Pin, LOCKER_VANDALIZED);
    			LockerStruct[2].isVandalized = 1;
      	}

      	if(HAL_GPIO_ReadPin(LockerStruct[3].Lock_Pin2.GPIOx, LockerStruct[3].Lock_Pin2.GPIO_Init.Pin) && (!LockerStruct[3].isVandalized)){
      			Lock_AddErrorLog (&LogsStruct[logsCount],LockerStruct[3].Lock_Pin1.GPIO_Init.Pin, LOCKER_VANDALIZED);
      			LockerStruct[3].isVandalized = 1;
      	}

      	if(HAL_GPIO_ReadPin(LockerStruct[4].Lock_Pin2.GPIOx, LockerStruct[4].Lock_Pin2.GPIO_Init.Pin) && (!LockerStruct[4].isVandalized)){
      			Lock_AddErrorLog (&LogsStruct[logsCount],LockerStruct[4].Lock_Pin1.GPIO_Init.Pin, LOCKER_VANDALIZED);
      			LockerStruct[4].isVandalized = 1;
      	}

	  if(!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))){


		  while(!Scanner_Configure(&UartHandle));

		  while(!Scanner_TurnOn(&UartHandle));

		  uint8_t aRxBuffer[SIZE_OF_QRCODE];
		  inOperation = 1;
		  uint32_t tickstart = HAL_GetTick();
		  uint32_t wait = TIMEOUT;

		  while((HAL_GetTick() - tickstart) < wait){

			  while(((HAL_GetTick() - tickstart) < wait) ){

				  if (Scanner_ReceiveQRCode(&UartHandle, (uint8_t*)aRxBuffer, SIZE_OF_QRCODE, QRREADER_TIMEOUT) == HAL_OK){
					  if(aRxBuffer[SIZE_OF_QRCODE-1] == '\r'){
							  break;
						  }
				  }
				  else{
					  memset(aRxBuffer, 0, SIZE_OF_QRCODE);
				  }

			  }
			  TYPE_QRCode_t state = Security_GetQRCodeType(aRxBuffer,CHECKSUM_COORD1,CHECKSUM_COORD2 , sizeof(aRxBuffer));
			  uint8_t locker_number;
			  switch(state){

				  case INVALID:
					  LED_RedTurnOn();
					  HAL_Delay(INVALID_LED_SIGNAL);
					  LED_RedTurnOff();
					  state = CONCLUDED;
					  break;
				  case MAILMAN:
					  locker_number = Security_GetLockerPosition(aRxBuffer, MAILMAN_LOCKER_COL_COORD, MAILMAN_LOCKER_LIN_COORD);
					  if (locker_number == 0){
						  state=INVALID;
						  break;
					  }
					  locker_number--;
					  if(LockerStruct[locker_number].isFull){
						  state = INVALID;
						  break;
					  }
					  if(Security_GetPin(&LockerStruct[locker_number], aRxBuffer, MAILMAN_PIN_COORD1, MAILMAN_PIN_COORD2, MAILMAN_PIN_COORD3, MAILMAN_PIN_COORD4)){

						  bool return_value = Lock_Toggle_Wait_Toggle(&LockerStruct[locker_number],LOCKER_WAITVALUE);
						  if (return_value == 0) Lock_AddErrorLog (&LogsStruct[logsCount],LockerStruct[locker_number].Lock_Pin1.GPIO_Init.Pin, LOCKER_FAILED_TO_OPEN);

						  LockerStruct[locker_number].isFull=1;
						  state = CONCLUDED;
						  Lock_SaveToFlash(&LockerStruct);
						  break;

					  }

					  state=INVALID;
					  break;
				  case CLIENT:
					  locker_number = Security_GetLockerPosition(aRxBuffer, CLIENT_LOCKER_COL_COORD, CLIENT_LOCKER_LIN_COORD);
					  if (locker_number == 0){
						  state=INVALID;
						  break;
					  }
					  locker_number--;
					  if(Security_ComparePins(&LockerStruct[locker_number], aRxBuffer, CLIENT_PIN_COORD1, CLIENT_PIN_COORD2, CLIENT_PIN_COORD3, CLIENT_PIN_COORD4, 0)){

						  bool return_value = Lock_Toggle_Wait_Toggle(&LockerStruct[locker_number],LOCKER_WAITVALUE);
						  if (return_value == 0) Lock_AddErrorLog (&LogsStruct[logsCount],LockerStruct[locker_number].Lock_Pin1.GPIO_Init.Pin, LOCKER_FAILED_TO_OPEN);

						  LockerStruct[locker_number].isFull=0;
 						  state = CONCLUDED;
 						  Lock_SaveToFlash(&LockerStruct);
						  break;
					  }
					  state=INVALID;
					  break;

				  case RECOVERY:
					  locker_number = Security_GetLockerPosition(aRxBuffer, RECOVERY_LOCKER_COL_COORD, RECOVERY_LOCKER_LIN_COORD);
					  if (locker_number == 0){
						  state=INVALID;
						  break;
					  }
					  locker_number--;
					  if(Security_ComparePins(&LockerStruct[locker_number], aRxBuffer, RECOVERY_PIN_COORD1, RECOVERY_PIN_COORD2, RECOVERY_PIN_COORD3, RECOVERY_PIN_COORD4,1)){

						  bool return_value = Lock_Toggle_Wait_Toggle(&LockerStruct[locker_number],LOCKER_WAITVALUE);
						  if (return_value == 0) Lock_AddErrorLog (&LogsStruct[logsCount],LockerStruct[locker_number].Lock_Pin1.GPIO_Init.Pin, LOCKER_FAILED_TO_OPEN);

						  LockerStruct[locker_number].isFull=0;
 						  state = CONCLUDED;
 						  Lock_SaveToFlash(&LockerStruct);
						  break;
					  }
					  state=INVALID;
					  break;
				  case MAINTENANCE:
					  uint8_t opcode =  Security_GetMaintOpType(aRxBuffer, MAINTENANCE_OPCODE_COORD1);
					  if(Security_ExecuteMaintOp(opcode, &LockerStruct)){
						  state = INVALID;
						  break;
					  }
					  state = CONCLUDED;
					  break;
				  case CONCLUDED:
					  inOperation = 0;
					  state++;
					  break;
				  default:
					  break;
			  }
			  memset(aRxBuffer, 0, SIZE_OF_QRCODE);
			  break;
		  }
	  }

  }
  /* USER CODE END 3 */
}

//function to deal with all interrupts
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{


    if (GPIO_Pin == GPIO_PIN_0)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);

    }

    if ((GPIO_Pin == GPIO_PIN_1 && (!inOperation))){

			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);

    }

    if ((GPIO_Pin == GPIO_PIN_3 && (!inOperation))){

			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);

    }

    if ((GPIO_Pin == GPIO_PIN_4 && (!inOperation))){

			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);

    }

    if ((GPIO_Pin == GPIO_PIN_7 && (!inOperation))){

			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);

    }

    if ((GPIO_Pin == GPIO_PIN_12 && (!inOperation))){

			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
    }

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}
/**
  * @brief  System Power Configuration
  *         The system Power is configured as follow :
  *            + System Running at MSI (~100 KHz)
  *            + Flash 0 wait state
  *            + Code running from Internal FLASH
  * @param  None
  * @retval None
  */
static void SystemPower_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

/* Enable GPIOs clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    /* Configure all GPIO port pins in Analog Input mode (floating input trigger OFF) */
    /* Note: Debug using ST-Link is not possible during the execution of this   */
    /*       example because communication between ST-link and the device       */
    /*       under test is done through UART. All GPIO pins are disabled (set   */
    /*       to analog input mode) including  UART I/O pins.           */
    GPIO_InitStructure.Pin = GPIO_PIN_All;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
    HAL_GPIO_Init(GPIOH, &GPIO_InitStructure);

    /* Disable GPIOs clock */
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();
    __HAL_RCC_GPIOC_CLK_DISABLE();
    __HAL_RCC_GPIOH_CLK_DISABLE();

}

/**
  * @brief  System Clock Speed decrease
  *         The system Clock source is shifted from HSI to MSI
  *         while at the same time, MSI range is set to RCC_MSIRANGE_0
  *         to go down to 100 KHz
  * @param  None
  * @retval None
  */
void SystemClock_Decrease(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* MSI is enabled after System reset, activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Disable HSI to reduce power consumption since MSI is used from that point */
  __HAL_RCC_HSI_DISABLE();

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
