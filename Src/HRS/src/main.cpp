#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#include <module_controllers/LEDController.hpp>

void setup()
{
    LEDController* controller = new LEDController(0);
    controller->bringOnline();
    controller->runScanningMode();
}

void loop()
{

}