/**
 * @file pinOperations.cpp
 * @author Talha Cetin (talhacetin96@hotmail.com)
 * @brief This source file contains pin related functions, 
 *        non-mapped and standart pin interrupt handlers.
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "globals.h"
#include "pinOperations.h"
#include "EnableInterrupt.h"

bool CANMessageReceived = false;

void InitPins()
{
    pinMode(BRUSHES_SPEED_CONTROL_PIN, OUTPUT);
    pinMode(BRUSHES_FORWARD_TURN_PIN , OUTPUT);
    pinMode(BRUSHES_STOP_PIN         , OUTPUT);
    pinMode(BRUSHES_REVERSE_TURN_PIN , OUTPUT);
    pinMode(BRUSHES_ERROR_PIN        , INPUT);

    pinMode(WATER_ON_OFF_PIN, OUTPUT);

    pinMode(TRACK_LEFT_SPEED_CONTROL_PIN, OUTPUT);
    pinMode(TRACK_LEFT_FORWARD_TURN_PIN , OUTPUT);
    pinMode(TRACK_LEFT_STOP_PIN         , OUTPUT);
    pinMode(TRACK_LEFT_REVERSE_TURN_PIN , OUTPUT);
    pinMode(TRACK_LEFT_ERROR_PIN        , INPUT);

    pinMode(TRACK_RIGHT_SPEED_CONTROL_PIN, OUTPUT);
    pinMode(TRACK_RIGHT_FORWARD_TURN_PIN , OUTPUT);
    pinMode(TRACK_RIGHT_STOP_PIN         , OUTPUT);
    pinMode(TRACK_RIGHT_REVERSE_TURN_PIN , OUTPUT);
    pinMode(TRACK_RIGHT_ERROR_PIN        , INPUT);

    pinMode(SENSOR_FRONT, INPUT);
    pinMode(SENSOR_REAR, INPUT);
    pinMode(SENSOR_LEFT, INPUT);
    pinMode(SENSOR_RIGHT, INPUT);

    pinModeExtended(PJ2, INPUT);

    enableInterrupt(CAN_INTERRUPT_PIN, MCP2515InterruptCallback, CHANGE);
}

void MCP2515InterruptCallback()
{
    if (digitalReadExtended(CAN_INTERRUPT_PIN) == LOW)
    {
        CANMessageReceived = true;
    }
    else if(digitalReadExtended(CAN_INTERRUPT_PIN) == HIGH)
    {
        CANMessageReceived = false;
    }
}

int digitalReadExtended(uint8_t pin)
{
    if (pin >= 70)
    {
        uint8_t bit = digitalPinToBitMask(PORT_J_FIRST_PIN);
        uint8_t port = digitalPinToPort(PORT_J_FIRST_PIN);

        uint8_t multiplier = pow(2, (pin - 69));
        if (*portInputRegister(port) & (bit * multiplier))   
        {
            return HIGH;
        }
        else
        {
            return LOW;
        }
    }
    else
    {
        return LOW;
    }
}

void digitalWriteExtended(uint8_t pin, uint8_t val)
{
    if (pin >= 70)
    {
        uint8_t bit = digitalPinToBitMask(PORT_J_FIRST_PIN);
        uint8_t port = digitalPinToPort(PORT_J_FIRST_PIN);
        volatile uint8_t *out;

        out = portOutputRegister(port);

        uint8_t oldSREG = SREG;
        cli();

        if (val == LOW) {
            *out &= ~(bit << (pin - 69));
        } else {
            *out |= (bit << (pin - 69));
        }

        SREG = oldSREG;
    }
}

void pinModeExtended(uint8_t pin, uint8_t ioMode)
{
    /* Only used for non-mapped MCP Interrupt pin */
    if (ioMode == INPUT)
    {
        DDRJ &= ~(1 << pin);
    }
    else if (ioMode == OUTPUT)
    {
        DDRJ |= (1 << pin);
    }
    else
    {
        DDRJ &= ~(1 << pin);
        PORTJ |= (1 << pin);
    }
}