#include <Arduino.h>
#include <modules/led.hpp>

void Led::led(uint8_t pinNum)
{
    this->pinNum = pinNum;
    isOn = false;
    brightness = 0;
}

void Led::init()
{
    pinMode(pinNum, OUTPUT);
    turnOff();
}

void Led::setBrightness(uint8_t brightness)
{
    this->brightness = brightness;

    // If already on, turn on again to update brightness
    if (isOn) 
    {
        turnOn();
    }
}

void Led::turnOn()
{
    analogWrite(pinNum, brightness);
    isOn = true;
}

void Led::turnOff()
{
    analogWrite(pinNum, 0);
    isOn = false;
}

bool Led::getIsOn()
{
    return isOn;
}