#include <module_controllers/RelayController.hpp>

RelayController::RelayController(uint8_t pinNum)
{
    relay = new Relay(pinNum);
}

RelayController::~RelayController()
{
    delete relay;
}

void RelayController::bringOnline()
{
    relay->init();
}

void RelayController::turnOn()
{
    relay->turnOn();
}

void RelayController::turnOff()
{
    relay->turnOff();
}