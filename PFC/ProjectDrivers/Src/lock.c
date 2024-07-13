/**
 * @file lock.c
 * @brief contains the API for the Lock of the system
 * @version 2
 * @date  10 Jun 2024
 * @author Carlos Ribeiro
 */

#include "lock.h"
#include "utils.h"


void Lock_Init(LockTypeDef *Lock){

	for(int i = 0; i<NUM_OF_LOCKERS; i++){
		  Lock_StructInit(&Lock[i], Lock_Pin1_GPIOx[i], Lock_Pin1[i],
		                 Lock_Pin2_GPIOx[i], Lock_Pin2[i]);

	}

}



void Lock_StructInit(LockTypeDef *Lock, GPIO_TypeDef *GPIOx1, uint16_t Pin1,
                     GPIO_TypeDef *GPIOx2, uint16_t Pin2) {

    Lock->Lock_Pin1.GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    Lock->Lock_Pin1.GPIO_Init.Pull = GPIO_PULLUP;
    Lock->Lock_Pin1.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    Lock->Lock_Pin1.GPIO_Init.Pin = Pin1;

    Lock->Lock_Pin1.GPIOx = GPIOx1;

    HAL_GPIO_Init(GPIOx1, &Lock->Lock_Pin1.GPIO_Init);

    Lock->Lock_Pin2.GPIO_Init.Mode = GPIO_MODE_IT_RISING ;
    Lock->Lock_Pin2.GPIO_Init.Pull = GPIO_PULLUP;
    Lock->Lock_Pin2.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    Lock->Lock_Pin2.GPIO_Init.Pin = Pin2;

    Lock->Lock_Pin2.GPIOx = GPIOx2;

    HAL_GPIO_Init(GPIOx2, &Lock->Lock_Pin2.GPIO_Init);


}

void Lock_Toggle(LockTypeDef *Lock) {

    HAL_GPIO_TogglePin(Lock->Lock_Pin1.GPIOx, Lock->Lock_Pin1.GPIO_Init.Pin);

}

bool Lock_Toggle_Wait_Toggle(LockTypeDef *Lock, uint8_t WaitMS){


	bool return_value = 0;

	Lock_Toggle(Lock);

	uint32_t tickstart = HAL_GetTick();
	uint32_t wait = WaitMS;
	while((HAL_GetTick() - tickstart) < wait){
		if(HAL_GPIO_ReadPin(Lock->Lock_Pin2.GPIOx, Lock->Lock_Pin2.GPIO_Init.Pin)){
			return_value = 1;
			break;
		}
	}

	Lock_Toggle(Lock);

	return return_value;

}

void Lock_AddErrorLog (Logs_TypeDef *Logs, uint32_t Pin, uint8_t errorCode){

		if (logsCount == NUM_OF_LOGS) logsCount= 0;
		Logs[logsCount].Locker_Pin = Pin;
		Logs[logsCount].Error_Code = errorCode;
		logsCount++;

}

void Lock_SaveToFlash(LockTypeDef *Lock) {
    SimplifiedLockTypeDef simplifiedLocks[NUM_OF_LOCKERS];
    for (int i = 0; i < NUM_OF_LOCKERS; i++) {
        ConvertLockToSimplified(&Lock[i], &simplifiedLocks[i]);
    }

    // Save the array of simplified locks to Flash memory
    WriteStructToFlash(FLASH_USER_START_ADDR, simplifiedLocks, sizeof(simplifiedLocks));
}

void Lock_ReadFromFlash(LockTypeDef *Lock) {
    if (!IsFlashDataValid()) {
        // Handle the case where no valid data is found
        return;
    }

    SimplifiedLockTypeDef simplifiedLocks[NUM_OF_LOCKERS];
    ReadStructFromFlash(FLASH_USER_START_ADDR, simplifiedLocks, sizeof(simplifiedLocks));

    for (int i = 0; i < NUM_OF_LOCKERS; i++) {
        Lock[i].isFull = simplifiedLocks[i].isFull;
        memcpy(Lock[i].PIN1, simplifiedLocks[i].PIN1, PIN_SIZE);
        memcpy(Lock[i].PIN2, simplifiedLocks[i].PIN2, PIN_SIZE);
        Lock[i].isVandalized = simplifiedLocks[i].isVandalized;
    }
}



