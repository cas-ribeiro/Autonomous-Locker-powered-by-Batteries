/**
 * @file security.c
 * @brief contains the API that will deal with all of the security of the Locker system
 * @version 1
 * @date  10 Jun 2024
 * @author Carlos Ribeiro
 */

#include "security.h"


uint8_t Security_GetQRCodeType(const uint8_t *array,uint8_t coord1, uint8_t coord2, size_t size) {

    if(array[coord1]+array[coord2]==MAILMAN_CHECKSUM) return MAILMAN;

    if(array[coord1]+array[coord2]==CLIENT_CHECKSUM) return CLIENT;

    if(array[coord1]+array[coord2]==MAINTENANCE_CHECKSUM) return MAINTENANCE;

    if(array[coord1]+array[coord2]==RECOVERY_CHECKSUM) return RECOVERY;

    return INVALID;
}

uint8_t Security_GetLockerPosition(const uint8_t *array, uint8_t coord_col, uint8_t coord_lin) {

    uint8_t col = array[coord_col];
    uint8_t lin = array[coord_lin];

    if(col >= '0' && col <= '9') col = col - '0';
    if(lin >= '0' && lin <= '9') lin = lin - '0';

    if (col > NUM_COLUMNS || lin > NUM_ROWS) {
        return 0;  // Invalid locker
    }


    uint8_t locker_number = lin * NUM_COLUMNS + col + 1; // +1 because lockers start from 1

    return locker_number;
}

uint8_t Security_GetPin(LockTypeDef *Lock, const uint8_t *array, uint8_t coord1, uint8_t coord2, uint8_t coord3, uint8_t coord4){

		Lock->PIN1[0]=array[coord1];
		Lock->PIN1[1]=array[coord2];
		Lock->PIN1[2]=array[coord3];
		Lock->PIN1[3]=array[coord4];

		Lock->PIN2[3]=array[coord1];
		Lock->PIN2[2]=array[coord2];
		Lock->PIN2[1]=array[coord3];
		Lock->PIN2[0]=array[coord4];

		return 1;
}

uint8_t Security_ComparePins(LockTypeDef *Lock, const uint8_t *array, uint8_t coord1, uint8_t coord2, uint8_t coord3, uint8_t coord4, bool clientNrecovery){


	if(!Lock->isFull) return 0;//if locker is full don't open for client

	uint8_t PIN[PIN_SIZE];

	PIN[0]=array[coord1];
	PIN[1]=array[coord2];
	PIN[2]=array[coord3];
	PIN[3]=array[coord4];
		if(!clientNrecovery){
			for (size_t i = 0; i < PIN_SIZE; i++) {
				if (Lock->PIN1[i] != PIN[i]) {
					return 0; // Arrays are different
				}
			}
		}

		if(clientNrecovery){
			for (size_t i = 0; i < PIN_SIZE; i++) {
				if (Lock->PIN2[i] != PIN[i]) {
					return 0; // Arrays are different
				}
			}
		}
	    return 1; // Arrays are the same
}

uint8_t Security_GetMaintOpType(const uint8_t *array, uint8_t coord1) {

    uint8_t Maint_Opcode = array[coord1];
    if(Maint_Opcode >= '0' && Maint_Opcode <= '9') Maint_Opcode = Maint_Opcode - '0';
    return Maint_Opcode;
}

uint8_t Security_ExecuteMaintOp(uint8_t maint_opcode, LockTypeDef *Lock){

	if(maint_opcode == OPEN_ALL_LOCKS){

		for(uint8_t i=0; i<NUM_OF_LOCKERS; i++){
			 bool return_value = Lock_Toggle_Wait_Toggle(&Lock[i],LOCKER_WAITVALUE);
             if (return_value == 0) Lock_AddErrorLog (&LogsStruct[logsCount],Lock[i].Lock_Pin1.GPIO_Init.Pin, LOCKER_FAILED_TO_OPEN);
             HAL_Delay(MAINT_WAIT);
		}

	return 1;

	}

	return 0;
}
