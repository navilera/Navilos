/*
 * Gpio.c
 *
 *  Created on: Jan 31, 2019
 *      Author: maanu
 */

#include "stm32f1xx_hal.h"
#include "HalGpio.h"

void Hal_gpio_init(void)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
}

