/**
 * @file scanner.c
 * @brief contains the API that will deal with QR Scanner of the Locker system
 * @version 1
 * @date  1 Jul 2024
 * @author Carlos Ribeiro
 */

#include "scanner.h"

uint8_t aRxBufferCheckSuccess[QRREADER_CODE_SUCESS_SIZE];

void Scanner_Init (UART_HandleTypeDef *UartHandle){

	  UartHandle->Instance = USART1;
	  UartHandle->Init.BaudRate = 9600;
	  UartHandle->Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle->Init.StopBits = UART_STOPBITS_1;
	  UartHandle->Init.Parity = UART_PARITY_NONE;
	  UartHandle->Init.Mode = UART_MODE_TX_RX;
	  UartHandle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  UartHandle->Init.OverSampling = UART_OVERSAMPLING_16;
	//  UartHandle->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	//  UartHandle->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	  if(HAL_UART_DeInit(UartHandle) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if(HAL_UART_Init(UartHandle) != HAL_OK)
	  {
	    Error_Handler();
	  }

}

uint8_t Scanner_Sleep (UART_HandleTypeDef *UartHandle){

	memset(aRxBufferCheckSuccess, 0, QRREADER_CODE_SUCESS_SIZE);

	HAL_UART_Transmit(UartHandle, (uint8_t*)turn_off_lights_command, QRREADER_CODE_SIZE, QRREADER_TIMEOUT);
	HAL_UART_Receive(UartHandle, (uint8_t*)aRxBufferCheckSuccess,  QRREADER_CODE_SUCESS_SIZE, QRREADER_TIMEOUT);

    // Check if the received buffer matches the expected success code
    if (memcmp(aRxBufferCheckSuccess, turn_off_lights_successful,  QRREADER_CODE_SUCESS_SIZE) == 0) {
        return 1;
    } else {
        return 0;
    }

}

uint8_t Scanner_Configure(UART_HandleTypeDef *UartHandle ){

	  memset(aRxBufferCheckSuccess, 0, QRREADER_CODE_SUCESS_SIZE);

	  HAL_UART_Transmit(UartHandle, (uint8_t*)configure_command, QRREADER_CODE_SIZE, QRREADER_TIMEOUT);
	  HAL_UART_Receive(UartHandle, (uint8_t*)aRxBufferCheckSuccess, QRREADER_CODE_SUCESS_SIZE, QRREADER_TIMEOUT);

	    if (memcmp(aRxBufferCheckSuccess, configure_successful, QRREADER_CODE_SUCESS_SIZE) != 0) {
	        return 0;
	    }

	  //memset(aRxBufferCheckSuccess, 0, QRREADER_CODE_SUCESS_SIZE);

	  HAL_UART_Transmit(UartHandle, (uint8_t*)configure2_command, QRREADER_CODE_SIZE, QRREADER_TIMEOUT);
	  HAL_UART_Receive(UartHandle, (uint8_t*)aRxBufferCheckSuccess, QRREADER_CODE_SUCESS_SIZE, QRREADER_TIMEOUT);

	    if (memcmp(aRxBufferCheckSuccess, configure_successful, QRREADER_CODE_SUCESS_SIZE) != 0) {
	        return 0;
	    }

	  //memset(aRxBufferCheckSuccess, 0, QRREADER_CODE_SUCESS_SIZE);

	  HAL_UART_Transmit(UartHandle, (uint8_t*)configure3_command, QRREADER_CODE_SIZE, QRREADER_TIMEOUT);
	  HAL_UART_Receive(UartHandle, (uint8_t*)aRxBufferCheckSuccess, QRREADER_CODE_SUCESS_SIZE, QRREADER_TIMEOUT);

	    if (memcmp(aRxBufferCheckSuccess, configure_successful, QRREADER_CODE_SUCESS_SIZE) != 0) {
	        return 0;
	    }


	  return 1;

}

uint8_t Scanner_TurnOn(UART_HandleTypeDef *UartHandle ){

	  memset(aRxBufferCheckSuccess, 0, QRREADER_CODE_SUCESS_SIZE);

	  HAL_UART_Transmit(UartHandle, (uint8_t*)turn_on_lights_command, QRREADER_CODE_SIZE, QRREADER_TIMEOUT);
	  HAL_UART_Receive(UartHandle, (uint8_t*)aRxBufferCheckSuccess,  QRREADER_CODE_SUCESS_SIZE, QRREADER_TIMEOUT);

	    if (memcmp(aRxBufferCheckSuccess, turn_on_lights_successful,  QRREADER_CODE_SUCESS_SIZE) == 0) {
	        return 1;
	    } else {
	        return 0;
	    }
}

uint8_t Scanner_ReceiveQRCode(UART_HandleTypeDef *UartHandle, const uint8_t *rcvBuffer, uint16_t Size, uint32_t Timeout){

	return (HAL_UART_Receive(UartHandle, (uint8_t*)rcvBuffer, Size, Timeout));

}


