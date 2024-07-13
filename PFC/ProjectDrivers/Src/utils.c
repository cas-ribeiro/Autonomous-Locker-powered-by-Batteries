/**
 * @file utils.c
 * @brief contains useful functions for Locker System
 * @version 1
 * @date  1 Jul 2024
 * @author Carlos Ribeiro
 */

#include "utils.h"

HAL_StatusTypeDef WriteStructToFlash(uint32_t address, void *data, size_t size) {
    HAL_StatusTypeDef status;
    uint64_t data64 = 0;

    // Unlock the Flash to enable the flash control register access
    HAL_FLASH_Unlock();

    // Clear any existing flags
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS);

    // Erase the specified flash page
    FLASH_EraseInitTypeDef eraseInitStruct;
    uint32_t pageError = 0;

    eraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    eraseInitStruct.Page        = GetPage(address);
    eraseInitStruct.NbPages     = 1;

    status = HAL_FLASHEx_Erase(&eraseInitStruct, &pageError);
    if (status != HAL_OK) {
        HAL_FLASH_Lock();
        return status;
    }

    // Program the flash double word by double word
    for (uint32_t i = 0; i < size; i += 8) {
        // Handle cases where size is not a multiple of 8
        if (i + 8 <= size) {
            data64 = *((uint64_t*)((uint8_t*)data + i));
        } else {
            // For the last chunk, if less than 8 bytes, pad with 0xFF
            uint8_t tempData[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
            uint32_t remainingBytes = size - i;
            for (uint32_t j = 0; j < remainingBytes; j++) {
                tempData[j] = *((uint8_t*)data + i + j);
            }
            data64 = *((uint64_t*)tempData);
        }

        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address + i, data64);
        if (status != HAL_OK) {
            HAL_FLASH_Lock();
            return status;
        }
    }

    // Lock the Flash to disable the flash control register access
    HAL_FLASH_Lock();

    return HAL_OK;
}



void ConvertLockToSimplified(const LockTypeDef *src, SimplifiedLockTypeDef *dst) {
    strncpy(dst->signature, FLASH_SIGNATURE, FLASH_SIGNATURE_SIZE);
    dst->isFull = src->isFull;
    memcpy(dst->PIN1, src->PIN1, PIN_SIZE);
    memcpy(dst->PIN2, src->PIN2, PIN_SIZE);
    dst->isVandalized = src->isVandalized;
}

void ReadStructFromFlash(uint32_t address, void *data, size_t size) {
    memcpy(data, (void*)address, size);
}


bool IsFlashDataValid(void) {
    SimplifiedLockTypeDef testLock;
    ReadStructFromFlash(FLASH_USER_START_ADDR, &testLock, sizeof(SimplifiedLockTypeDef));
    return strncmp(testLock.signature, FLASH_SIGNATURE, FLASH_SIGNATURE_SIZE) == 0;
}

// Helper function to get the page of a given address
uint32_t GetPage(uint32_t addr) {
	  uint32_t page = 0;

	  if (addr < (FLASH_BASE + FLASH_BANK_SIZE))
	  {
	    /* Bank 1 */
	    page = (addr - FLASH_BASE) / FLASH_PAGE_SIZE;
	  }
	  else
	  {
	    /* Bank 2 */
	    page = (addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
	  }

	  return page;
}

