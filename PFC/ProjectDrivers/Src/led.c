/**
 * @file led.c
 * @brief contains the API that will deal with LED of the Locker system
 * @version 1
 * @date  1 Jul 2024
 * @author Carlos Ribeiro
 */

#include "led.h"

void LED_Init (void){

	  GPIO_InitTypeDef  GPIO_InitStruct;

	  GPIO_InitStruct.Pin = GPIO_PIN_6;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull  = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = GPIO_PIN_7;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull  = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void LED_RedTurnOn (void){

	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);

}

void LED_RedTurnOff (void){

	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);

}

void LED_BlueTurnOn (void){

	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);

}

void LED_BlueTurnOff (void){

	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);

}
