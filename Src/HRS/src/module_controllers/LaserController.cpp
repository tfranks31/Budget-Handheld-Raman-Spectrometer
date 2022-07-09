#include <module_controllers/LaserController.hpp>

LaserController::LaserController(uint8_t pinNum)
{
    laser = new Laser(pinNum);
}

LaserController::~LaserController()
{
    delete laser;
}

void LaserController::bringOnline()
{
    laser->init();
}

void LaserController::turnOn()
{
    laser->turnOn();
}

void LaserController::turnOff()
{
    laser->turnOff();
}

void LaserController::setIntensity(uint8_t intensity)
{
    laser->setIntensity(intensity);
}