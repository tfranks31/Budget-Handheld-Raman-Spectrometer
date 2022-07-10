#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#include <module_controllers/LEDController.hpp>
#include <module_controllers/LaserController.hpp>
#include <module_controllers/JoystickController.hpp>
JoystickController* jcntr = new JoystickController(22, 21, 1);
void setup()
{
    LEDController* controller = new LEDController(0);
    controller->bringOnline();
    controller->runScanningMode();

    LaserController* lcntr = new LaserController(9);
    lcntr->bringOnline();
    lcntr->setIntensity(255);
    lcntr->turnOn();

    
    jcntr->bringOnline();
}

void loop()
{
    Serial.println(jcntr->getHorizontalMovement());
    Serial.println(jcntr->getVerticalMovement());
    Serial.println(jcntr->getButtonPressed());
    Serial.println();
    jcntr->clearButtonPressed();
    delay(500);
}