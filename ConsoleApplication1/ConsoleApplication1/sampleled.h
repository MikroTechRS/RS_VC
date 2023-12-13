/**
 * @file sampleled.h
 * @author Marc Sandusky (marc_sandusky@outlook.com)
 * @brief Support for the sample LED
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef INC_SAMPLELED_H_
#define INC_SAMPLELED_H_

#include <stm32f4xx_hal.h>

#include <gpioext.h>

/**
 * @brief List of possible sample LED modes
 * 
 */
typedef enum sampleled_mode {
    SAMPLELED_OFF,
    SAMPLELED_ON
} Sampleled_Mode;

HAL_StatusTypeDef sampleled_mode(Sampleled_Mode mode);
HAL_StatusTypeDef sampleled_init(GPIOEXT_Port port, GPIOEXT_Pin pin);

#endif  // INC_SAMPLELED_H_
