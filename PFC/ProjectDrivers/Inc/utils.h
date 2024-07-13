/**
 * @file utils.h
 * @brief contains useful functions for Locker System
 * @version 1
 * @date  1 Jul 2024
 * @author Carlos Ribeiro
 */

/**
 * @addtogroup PROJECT_DRIVERS
* @brief This package provides project drivers for the CTT Locker System.
* @{
 */
/** @defgroup UTILS UTILS
* @brief Provides the core functions for the Locker System.
* @{
* */



#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "lock.h"


/**
 * @brief Writes a structure to Flash memory.
 * @param address: The start address in Flash where the data will be written.
 * @param data: Pointer to the data to be written.
 * @param size: Size of the data to be written in bytes.
 * @return HAL_StatusTypeDef indicating the status of the operation.
 */
HAL_StatusTypeDef WriteStructToFlash(uint32_t address, void *data, size_t size);


/**
 * @brief Converts a LockTypeDef structure to a SimplifiedLockTypeDef structure.
 * @param src: Pointer to the source LockTypeDef structure.
 * @param dst: Pointer to the destination SimplifiedLockTypeDef structure.
 */
void ConvertLockToSimplified(const LockTypeDef *src, SimplifiedLockTypeDef *dst);


/**
 * @brief Reads a structure from Flash memory.
 * @param address: The start address in Flash where the data will be read from.
 * @param data: Pointer to the buffer where the data will be stored.
 * @param size: Size of the data to be read in bytes.
 */
void ReadStructFromFlash(uint32_t address, void *data, size_t size);


/**
 * @brief Checks if the Flash data is valid by verifying the signature.
 * @return true if the data is valid, otherwise false.
 */
bool IsFlashDataValid(void);


/**
 * @brief Gets the Flash page number for a given address.
 * @param addr: The address for which to find the page number.
 * @return The page number corresponding to the given address.
 */
uint32_t GetPage(uint32_t addr);

/**
 * @}
 */
/**
 * @}
 */

#endif /* INC_UTILS_H_ */
