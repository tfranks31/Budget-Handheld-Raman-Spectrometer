#include <Arduino.h>
#include <modules/Joystick.hpp>

/**
 * The pin number that the button is hooked up to.
 */
uint8_t Joystick::buttonPinNum;

/**
 * Whether or not the button was pressed since the last clear.
 */
bool Joystick::wasButtonPressed;

/**
 * Interval timer to detect bouncing on release of the button.
 */
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
    timer->begin(confirmButtonPress, BOUNCE_TIME);
}

void Joystick::confirmButtonPress()
{
    if (digitalRead(buttonPinNum) == LOW)
    {
        wasButtonPressed = true;
    }

    timer->end();
}