/**
 * @file led.h
 * @brief contains the API that will deal with the LED of the Locker system.
 * @version 1
 * @date  1 Jul 2024
 * @author Carlos Ribeiro
 */

/**
 * @addtogroup PROJECT_DRIVERS
* @brief This package provides project drivers for the CTT Locker System.
* @{
 */
/** @defgroup LED LED
* @brief Provides the core capabilities for the LED of the Locker System.
* @{
* */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "stm32l4xx_hal.h"

/**
 * @brief Initializes the GPIO pins for the LEDs.
 */
void LED_Init (void);

/**
 * @brief Turns on the red LED.
 */
void LED_RedTurnOn (void);

/**
 * @brief Turns off the red LED.
 */
void LED_RedTurnOff (void);

/**
 * @brief Turns on the blue LED.
 */
void LED_BlueTurnOn (void);

/**
 * @brief Turns off the blue LED.
 */
void LED_BlueTurnOff (void);

/**
 * @}
 */
/**
 * @}
 */

#endif /* INC_LED_H_ */
