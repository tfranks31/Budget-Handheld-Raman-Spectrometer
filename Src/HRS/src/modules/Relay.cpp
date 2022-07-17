#include <Arduino.h>
#include <modules/Relay.hpp>

Relay::Relay(uint8_t pinNum)
{
    this->pinNum = pinNum;
}

void Relay::init()
{
    pinMode(pinNum, OUTPUT);
    turnOff();
}

void Relay::turnOn()
{
    digitalWrite(pinNum, HIGH);
    isOn = true;
}

void Relay::turnOff()
{
    digitalWrite(pinNum, LOW);
    isOn = false;
}

bool Relay::getIsOn()
{
    return isOn;
}