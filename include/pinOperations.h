/**
 * @file pinOperations.h
 * @author Talha Cetin (talhacetin96@hotmail.com)
 * @brief This header file contains pin related functions, 
 *        non-mapped and standart pin interrupt handlers.
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PIN_OPERATIONS_H_
#define _PIN_OPERATIONS_H_

#include <Arduino.h>
#include "pinDefinitions.h"
#include "threadSafeSerial.h"
#include "math.h"

#define PORT_J_FIRST_PIN    14

enum
{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    PORT_H,
    PORT_J,
    PORT_K,
    PORT_L,
};

/**
 * @brief This function initializes pins IO modes and enables interrupts.
 * 
 */
void InitializePins(void);

/**
 * @brief Thread safe digitalRead() with extended pins
 * 
 * @param pin pin number
 * @return int value
 */
int DigitalReadThreadSafe(uint8_t pin);

/**
 * @brief Thread safe digitalWrite() with extended pins
 * 
 * @param pin pin number
 * @return int value
 */
void DigitalWriteThreadSafe(uint8_t pin, uint8_t val);

/**
 * @brief Thread safe analogWrite() with extended pins
 * 
 * @param pin pin number
 * @param val value
 */
void AnalogWriteThreadSafe(uint8_t pin, uint8_t val);

/**
 * @brief Thread safe analogRead()
 * 
 * @param pin pin number
 * @return int value
 */
int AnalogReadThreadSafe(uint8_t pin);

/**
 * @brief This function is used for non-mapped pin's digitalRead operation.
 * 
 * @param pin A non-mapped pin's fake pin number from "pinDefinitions.h".
 * @return int Value of the pin as HIGH or LOW.
 */
int digitalReadExtended(uint8_t pin);

/**
 * @brief This function is created to set pinMode to a 
 *        non-mapped pin but can be used for all pins.
 * 
 * @param port Port define of the pin like for "PJ2" pin it's "PORT_J".
 * @param pin Defined name of the pin like "PJ2".
 * @param ioMode INPUT, OUTPUT or INPUT_PULLUP.
 */
void pinModeExtended(uint8_t port, uint8_t pin, uint8_t ioMode);

/**
 * @brief This function is used for non-mapped pin's digitalWrite operation.
 * 
 * @param pin A non-mapped pin's fake pin number from "pinDefinitions.h".
 * @return int Value of write to pin as HIGH or LOW.
 */
void digitalWriteExtended(uint8_t pin, uint8_t val);

/**
 * @brief Callback function of MCP2515 CanBUS module's interrupt pin.
 * 
 */
void MCP2515InterruptCallback(void);

/**
 * @brief Encoder 1's A pin interrupt callback
 * 
 */
void Encoder1InterruptACallback(void);

/**
 * @brief Encoder 1's B pin interrupt callback
 * 
 */
void Encoder1InterruptBCallback(void);

/**
 * @brief Encoder 1's 0 pin interrupt callback
 * 
 */
void Encoder1Interrupt0Callback(void);

/**
 * @brief Encoder 2's A pin interrupt callback
 * 
 */
void Encoder2InterruptACallback(void);

/**
 * @brief Encoder 2's B pin interrupt callback
 * 
 */
void Encoder2InterruptBCallback(void);

/**
 * @brief Encoder 2's 0 pin interrupt callback
 * 
 */
void Encoder2Interrupt0Callback(void);

#endif /* _PIN_OPERATIONS_H_ */