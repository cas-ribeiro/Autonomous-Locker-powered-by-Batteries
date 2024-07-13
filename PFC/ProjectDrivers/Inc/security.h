/**
 * @file security.h
 * @brief contains the API that will deal with all of the security of the Locker system
 * @version 1
 * @date  10 Jun 2024
 * @author Carlos Ribeiro
 */

/**
 * @addtogroup PROJECT_DRIVERS
* @brief This package provides project drivers for the CTT Locker System.
* @{
 */
/** @defgroup SECURITY SECURITY
* @brief Provides the core capabilities for the security needs of the Locker System
* @{
* */

#ifndef INC_SECURITY_H_
#define INC_SECURITY_H_

#include "lock.h"
#include "stdbool.h"

#include "stm32l4xx_hal.h"

#define MAILMAN_CHECKSUM 150
#define CLIENT_CHECKSUM 155
#define MAINTENANCE_CHECKSUM 160
#define RECOVERY_CHECKSUM 165

#define SIZE_OF_QRCODE 13

#define CHECKSUM_COORD1 0
#define CHECKSUM_COORD2 1

#define INVALID_LED_SIGNAL 1000
#define MAINT_WAIT 1500

//MAILMAN COORDS
#define MAILMAN_LOCKER_LIN_COORD 2
#define MAILMAN_LOCKER_COL_COORD 5
#define MAILMAN_PIN_COORD1 3
#define MAILMAN_PIN_COORD2 6
#define MAILMAN_PIN_COORD3 8
#define MAILMAN_PIN_COORD4 9

//CLIENT COORDS
#define CLIENT_LOCKER_LIN_COORD 3
#define CLIENT_LOCKER_COL_COORD 6
#define CLIENT_PIN_COORD1 2
#define CLIENT_PIN_COORD2 5
#define CLIENT_PIN_COORD3 8
#define CLIENT_PIN_COORD4 9

//RECOVERY COORDS
#define RECOVERY_LOCKER_LIN_COORD 3
#define RECOVERY_LOCKER_COL_COORD 6
#define RECOVERY_PIN_COORD1 2
#define RECOVERY_PIN_COORD2 5
#define RECOVERY_PIN_COORD3 8
#define RECOVERY_PIN_COORD4 9

//MAINTENANCE COORDS
#define MAINTENANCE_OPCODE_COORD1 5

typedef enum MaintOPEnum{
		OPEN_ALL_LOCKS
}MAINT_OP_t;

typedef enum TypeofQRCodeEnum{
		INVALID,
		MAILMAN,
		CLIENT,
		MAINTENANCE,
		RECOVERY,
		CONCLUDED
}TYPE_QRCode_t;

/**
 * @brief Determines the type of QR code based on checksum.
 * @param array: Array containing QR code data.
 * @param coord1: First coordinate for checksum calculation.
 * @param coord2: Second coordinate for checksum calculation.
 * @param size: Size of the array.
 * @return Type of QR code (MAILMAN, CLIENT, MAINTENANCE, RECOVERY, or INVALID).
 */
uint8_t Security_GetQRCodeType(const uint8_t *array,uint8_t coord1, uint8_t coord2, size_t size);

/**
 * @brief Retrieves the locker position based on coordinates.
 * @param array: Array containing locker data.
 * @param coord_col: Column coordinate.
 * @param coord_lin: Line coordinate.
 * @return Locker number if valid; otherwise, 0 for invalid locker.
 */
uint8_t Security_GetLockerPosition(const uint8_t *array, uint8_t coord_col, uint8_t coord_lin);

/**
 * @brief Retrieves the PIN from array data and stores it in the LockTypeDef structure.
 * @param Lock: Pointer to the LockTypeDef structure to store PINs.
 * @param array: Array containing PIN data.
 * @param coord1: First PIN coordinate.
 * @param coord2: Second PIN coordinate.
 * @param coord3: Third PIN coordinate.
 * @param coord4: Fourth PIN coordinate.
 * @return 1 if successful.
 */
uint8_t Security_GetPin(LockTypeDef *Lock, const uint8_t *array, uint8_t coord1, uint8_t coord2, uint8_t coord3, uint8_t coord4);

/**
 * @brief Compares the provided PIN with the one stored in the LockTypeDef structure.
 * @param Lock: Pointer to the LockTypeDef structure containing the stored PINs.
 * @param array: Array containing PIN data to compare.
 * @param coord1: First PIN coordinate.
 * @param coord2: Second PIN coordinate.
 * @param coord3: Third PIN coordinate.
 * @param coord4: Fourth PIN coordinate.
 * @param clientNrecovery: Flag indicating whether the operation is for client or recovery.
 * @return 1 if the PINs match; otherwise, 0.
 */
uint8_t Security_ComparePins(LockTypeDef *Lock, const uint8_t *array, uint8_t coord1, uint8_t coord2, uint8_t coord3, uint8_t coord4, bool clientNrecovery);

/**
 * @brief Retrieves the maintenance operation type based on the opcode in the array.
 * @param array: Array containing maintenance data.
 * @param coord1: Coordinate of the opcode.
 * @return Maintenance operation type.
 */
uint8_t Security_GetMaintOpType(const uint8_t *array, uint8_t coord1);

/**
 * @brief Executes the maintenance operation based on the given opcode.
 * @param maint_op Maintenance operation to execute.
 * @param Lock Pointer to the LockTypeDef structure for lock operations.
 * @return 1 if successful; otherwise, 0.
 */
uint8_t Security_ExecuteMaintOp(uint8_t maint_op, LockTypeDef *Lock);

/**
 * @}
 */
/**
 * @}
 */

#endif /* INC_SECURITY_H_ */
