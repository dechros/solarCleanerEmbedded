/**
 * @file globals.h
 * @author Halit Cetin (halitcetin@live.com)
 * @brief This file includes global variables.
 * @version 0.1
 * @date 04-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <Arduino.h>
#include "Arduino_FreeRTOS.h"

extern TaskHandle_t xSerialParserTaskHandle;
extern TaskHandle_t xSecondTaskHandle;

#endif /* _GLOBALS_H_ */