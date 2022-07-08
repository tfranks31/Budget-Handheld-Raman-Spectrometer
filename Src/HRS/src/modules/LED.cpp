#include <Arduino.h>
#include <modules/LED.hpp>

LED::LED(uint8_t pinNum)
{
    this->pinNum = pinNum;
    isOn = false;
    brightness = 0;
}

void LED::init()
{
    pinMode(pinNum, OUTPUT);
    turnOff();
}

uint8_t LED::getBrightness()
{
    return brightness;
}

void LED::setBrightness(uint8_t brightness)
{
    this->brightness = brightness;

    // If already on, turn on again to update brightness
    if (isOn) 
    {
        turnOn();
    }
}

void LED::turnOn()
{
    analogWrite(pinNum, brightness);
    isOn = true;
}

void LED::turnOff()
{
    analogWrite(pinNum, 0);
    isOn = false;
}

bool LED::getIsOn()
{
    return isOn;
}