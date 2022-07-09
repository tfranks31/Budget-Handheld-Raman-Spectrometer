#include <Arduino.h>
#include <modules/Joystick.hpp>

Joystick::Joystick(uint8_t xPinNum, uint8_t yPinNum, uint8_t buttonPinNum)
{
    this->xPinNum = xPinNum;
    this->yPinNum = yPinNum;
    this->buttonPinNum = buttonPinNum;
}

void Joystick::init()
{
    // Analog pins do not need to be declared as inputs
    pinMode(buttonPinNum, INPUT);
    clearButtonPress();
    attachInterrupt(buttonPinNum, handleButtonPress, RISING);
}

uint16_t Joystick::getXPos()
{
    return analogRead(xPinNum);
}

uint16_t Joystick::getYPos()
{
    return analogRead(yPinNum);
}

bool Joystick::getButtonPressed()
{
    return wasButtonPressed;
}

void Joystick::clearButtonPress()
{
    wasButtonPressed = false;
}

void Joystick::handleButtonPress()
{
    wasButtonPressed = true;
}