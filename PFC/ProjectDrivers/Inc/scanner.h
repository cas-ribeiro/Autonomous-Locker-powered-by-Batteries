/**
 * @file scanner.h
 * @brief contains the API that will deal with QR Scanner of the Locker system
 * @version 1
 * @date  1 Jul 2024
 * @author Carlos Ribeiro
 */


/**
 * @addtogroup PROJECT_DRIVERS
* @brief This package provides project drivers for the CTT Locker System.
* @{
 */
/** @defgroup SCANNER SCANNER
* @brief Provides the core capabilities for the QR Scanner of the Locker System.
* @{
* */


#ifndef INC_SCANNER_H_
#define INC_SCANNER_H_

#include "stm32l4xx_hal.h"

#define QRREADER_CODE_SIZE 9
#define QRREADER_CODE_SUCESS_SIZE 7
#define QRREADER_TIMEOUT 500

//commands to send to the scanner
static volatile uint8_t turn_off_lights_command [QRREADER_CODE_SIZE] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00, 0xAB, 0xCD};
static volatile uint8_t sleep_command[QRREADER_CODE_SIZE] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0xD9, 0xA5, 0xAB, 0xCD};
static volatile uint8_t turn_on_command[QRREADER_CODE_SIZE] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0xD9, 0x00, 0xAB, 0xCD};
static volatile uint8_t turn_on_lights_command [QRREADER_CODE_SIZE] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x00, 0xFE, 0xAB, 0xCD};
static volatile uint8_t configure_command[QRREADER_CODE_SIZE] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x0D, 0x00, 0xAB, 0xCD};
static volatile uint8_t configure2_command[QRREADER_CODE_SIZE] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x2B, 0x01, 0xAB, 0xCD};
static volatile uint8_t configure3_command[QRREADER_CODE_SIZE] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x2A, 0x39, 0xAB, 0xCD};


//success commands return
static volatile uint8_t turn_off_lights_successful[QRREADER_CODE_SUCESS_SIZE] = { 0x02, 0x00, 0x00, 0x01, 0x00, 0x33, 0x31};
static volatile uint8_t configure_successful[QRREADER_CODE_SUCESS_SIZE] = {  0x02, 0x00, 0x00, 0x01, 0x00, 0x33, 0x31};
static volatile uint8_t turn_on_lights_successful[QRREADER_CODE_SUCESS_SIZE] = { 0x02, 0x00, 0x00, 0x01, 0x00, 0x33, 0x31};

/**
 * @brief Sends the sleep command to the QR scanner and checks the response.
 * @param UartHandle: Pointer to a UART_HandleTypeDef structure that contains
 *                    the configuration information for the specified UART module.
 * @return 1 if the response matches the expected success code, otherwise 0.
 */
void Scanner_Init (UART_HandleTypeDef *UartHandle);

/**
 * @brief Sends the sleep command to the QR scanner and checks the response.
 * @param UartHandle: Pointer to a UART_HandleTypeDef structure that contains
 *                    the configuration information for the specified UART module.
 * @return 1 if the response matches the expected success code, otherwise 0.
 */
uint8_t Scanner_Sleep (UART_HandleTypeDef *UartHandle);

/**
 * @brief Sends configuration commands to the QR scanner and checks the responses.
 * @param UartHandle: Pointer to a UART_HandleTypeDef structure that contains
 *                    the configuration information for the specified UART module.
 * @return 1 if all responses match the expected success code, otherwise 0.
 */
uint8_t Scanner_Configure(UART_HandleTypeDef *UartHandle);

/**
 * @brief Sends the command to turn on the lights of the QR scanner and checks the response.
 * @param UartHandle: Pointer to a UART_HandleTypeDef structure that contains
 *                    the configuration information for the specified UART module.
 * @return 1 if the response matches the expected success code, otherwise 0.
 */
uint8_t Scanner_TurnOn(UART_HandleTypeDef *UartHandle );

/**
 * @brief Receives a QR code via UART.
 * @param UartHandle: Pointer to a UART_HandleTypeDef structure that contains
 *                    the configuration information for the specified UART module.
 * @param rcvBuffer: Pointer to the buffer where the received QR code will be stored.
 * @param Size: Size of the buffer.
 * @param Timeout: Timeout duration for the receive operation.
 * @return HAL status of the receive operation.
 */
uint8_t Scanner_ReceiveQRCode(UART_HandleTypeDef *UartHandle, const uint8_t *rcvBuffer, uint16_t Size, uint32_t Timeout);

/**
 * @}
 */
/**
 * @}
 */

#endif /* INC_SCANNER_H_ */
