#include <Arduino.h>
#include <modules/Laser.hpp>

Laser::Laser(uint8_t pinNum)
{
    this->pinNum = pinNum;
    isOn = false;
    intensity = 0;
}

void Laser::init()
{
    pinMode(pinNum, OUTPUT);
    turnOff();
}

void Laser::setIntensity(uint8_t intensity)
{
    this->intensity = intensity;

    // If already on, turn on again to update intensity
    if (isOn) 
    {
        turnOn();
    }
}

void Laser::turnOn()
{
    analogWrite(pinNum, intensity);
    isOn = true;
}

void Laser::turnOff()
{
    analogWrite(pinNum, 0);
    isOn = false;
}

bool Laser::getIsOn()
{
    return isOn;
}