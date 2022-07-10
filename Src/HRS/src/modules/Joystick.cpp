#include <Arduino.h>
#include <modules/Joystick.hpp>

bool Joystick::wasButtonPressed;
uint8_t Joystick::buttonPinNum;
IntervalTimer* Joystick::timer;

Joystick::Joystick(uint8_t xPinNum, uint8_t yPinNum, uint8_t buttonPinNum)
{
    this->xPinNum = xPinNum;
    this->yPinNum = yPinNum;
    this->buttonPinNum = buttonPinNum;
    timer = new IntervalTimer();
}

Joystick::~Joystick()
{
    delete timer;
}

void Joystick::init()
{
    // Analog pins do not need to be declared as inputs
    pinMode(buttonPinNum, INPUT_PULLUP);
    clearButtonPress();
    attachInterrupt(buttonPinNum, handleButtonPress, FALLING);
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
    timer->begin(confirmButtonPress, 500);
}

void Joystick::confirmButtonPress()
{
    if (digitalRead(buttonPinNum) == LOW)
    {
        wasButtonPressed = true;
    }

    timer->end();
}