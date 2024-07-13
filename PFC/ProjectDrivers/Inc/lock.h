/**
 * @file lock.h
 * @brief contains the API for the Lock of the system
 * @version 2
 * @date  10 Jun 2024
 * @author Carlos Ribeiro
 */

/**
 * @defgroup PROJECT_DRIVERS PROJECT_DRIVERS
* @brief This package provides project drivers for the CTT Locker System.
* @{
 */
/** @defgroup LOCK LOCK
* @brief Provides the core capabilities for the Lock.
* @{
* */

#ifndef INC_LOCK_H_
#define INC_LOCK_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"
#include "stm32l4xx_hal_flash_ex.h"

#include <stdbool.h>
#include <string.h>



#define PIN_SIZE 4

#define NUM_OF_LOGS 100
#define NUM_OF_LOCKERS 5
#define NUM_COLUMNS 3
#define NUM_ROWS 2

#define LOCKER_WAITVALUE 800


//ERROR DEFINES
#define LOCKER_FAILED_TO_OPEN 110
#define LOCKER_VANDALIZED     120

#define FLASH_USER_START_ADDR   0x0801F800   // Starting address in Flash for Page 63
#define FLASH_USER_END_ADDR     0x0801FFFF // End address of last page (Page 63)
#define FLASH_SIGNATURE         "CTTLOCKY"           // Signature to indicate valid data
#define FLASH_SIGNATURE_SIZE    8                    // Length of the signature

typedef struct {
    char signature[FLASH_SIGNATURE_SIZE];
    bool isFull;
    uint8_t PIN1[PIN_SIZE];
    uint8_t PIN2[PIN_SIZE];
    bool isVandalized;
}SimplifiedLockTypeDef;

typedef struct{

	uint16_t Locker_Pin;

	uint8_t Error_Code;

}Logs_TypeDef;

typedef struct
{
	GPIO_TypeDef *GPIOx; // Port of the GPIO

	GPIO_InitTypeDef GPIO_Init; // Struct to initialize GPIO and also hold the Pin number

}Lock_PinTypeDef; //Holds the structures needed to utilize a GPIO for the Lock

typedef struct
{

	Lock_PinTypeDef Lock_Pin1; // GPIO to open and close the Lock

	Lock_PinTypeDef Lock_Pin2; // GPIO to inform the system of unauthorized opening

	bool isFull; //Tells the user if the lock is full or not

	uint8_t PIN1[PIN_SIZE];//QR code portion that will open this lock if it is full and its a client

	uint8_t PIN2[PIN_SIZE];//QR code portion that will open this lock if it is full and its recovery

	bool isVandalized ;

	//enum sizeOfLock // Indicates the size of the locker this lock supports

}LockTypeDef;//Data structure that holds all the necessary variables for a given Lock

//variables that hold all the values to initialize the LockerStruct, will be used in Lock_Init

static  LockTypeDef LockerStruct[NUM_OF_LOCKERS];

static volatile Logs_TypeDef LogsStruct[NUM_OF_LOGS];

static volatile uint16_t Lock_Pin1[NUM_OF_LOCKERS] = {GPIO_PIN_1,GPIO_PIN_8,GPIO_PIN_6,GPIO_PIN_5,GPIO_PIN_11};

static volatile uint16_t Lock_Pin2[NUM_OF_LOCKERS] = {GPIO_PIN_12,GPIO_PIN_1,GPIO_PIN_7,GPIO_PIN_4,GPIO_PIN_3};

static volatile GPIO_TypeDef *Lock_Pin1_GPIOx[NUM_OF_LOCKERS] = {GPIOB,GPIOA,GPIOB,GPIOA,GPIOA};

static volatile GPIO_TypeDef *Lock_Pin2_GPIOx[NUM_OF_LOCKERS] = {GPIOA,GPIOA,GPIOA,GPIOA,GPIOA};

static volatile uint8_t logsCount = 0; // variable that holds the current number of logs being kept

static volatile bool inOperation = 0; // value that tells the system to ignore feedback pins during operation

/**
 * @brief Initializes the lock system.
 * @param Lock: Pointer to an array of LockTypeDef structures.
 */
void Lock_Init(LockTypeDef *Lock);

/**
 * @brief Initializes the lock structure.
 * @param Lock: Pointer to a LockTypeDef structure.
 * @param GPIOx1: Pointer to the GPIO port for Lock_Pin1.
 * @param Pin1: Pin number for Lock_Pin1.
 * @param GPIOx2: Pointer to the GPIO port for Lock_Pin2.
 * @param Pin2: Pin number for Lock_Pin2.
 */
void Lock_StructInit (LockTypeDef *Lock ,GPIO_TypeDef  *GPIOx1 ,uint16_t Pin1 ,GPIO_TypeDef  *GPIOx2 ,uint16_t Pin2);

/**
 * @brief Toggles the lock state.
 * @param Lock: Pointer to a LockTypeDef structure.
 */
void Lock_Toggle(LockTypeDef *Lock);

/**
 * @brief Toggles the lock state, waits for a specified time, and then toggles back.
 * @param Lock: Pointer to a LockTypeDef structure.
 * @param WaitMS: Time to wait in milliseconds.
 * @return true if unauthorized opening is detected, otherwise false.
 */
bool Lock_Toggle_Wait_Toggle(LockTypeDef *Lock, uint8_t WaitMS);


/**
 * @brief Adds an error log entry.
 * @param Logs: Pointer to an array of Logs_TypeDef structures.
 * @param Pin: Pin number associated with the log.
 * @param errorCode: Error code to log.
 */
void Lock_AddErrorLog (Logs_TypeDef *Logs, uint32_t Pin, uint8_t errorCode);


/**
 * @brief Saves the lock state to Flash memory.
 * @param Lock: Pointer to an array of LockTypeDef structures.
 */
void Lock_SaveToFlash(LockTypeDef *Lock);


/**
 * @brief Reads the lock state from Flash memory.
 * @param Lock: Pointer to an array of LockTypeDef structures.
 */
void Lock_ReadFromFlash(LockTypeDef *Lock);



/**
 * @}
 */
/**
 * @}
 */

#endif /* INC_LOCK_H_ */
