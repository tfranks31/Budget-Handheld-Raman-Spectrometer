#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_ST7789.h>
#include <module_controllers/LEDController.hpp>
#include <module_controllers/LaserController.hpp>
#include <module_controllers/JoystickController.hpp>
JoystickController* jcntr = new JoystickController(22, 21, 1);
Adafruit_ST7789 tft = Adafruit_ST7789(10, 5, 7);
LaserController* lcntr = new LaserController(9);
LEDController* controller = new LEDController(0);
int xPos = 0, yPos = 0;
bool grid[2][2] = {{false, false}, {false, true}};
bool laserOn = false;
int oldX = 0, oldY = 0;

void setup()
{
    
    controller->bringOnline();

    
    lcntr->bringOnline();
    lcntr->setIntensity(255);
    
    jcntr->bringOnline();

    
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);

    tft.init(170,320);
    tft.setFont();
    tft.fillScreen(0x0000);
    tft.setTextColor(0x0FF0);
    tft.setTextSize(2);

    tft.setRotation(2);

    tft.fillRect(10, 10, 70, 70, 0xFFFF);
    tft.drawRect(90, 10, 70, 70, 0xFFFF);
    tft.drawRect(10, 90, 70, 70, 0xFFFF);
    tft.drawRect(90, 90, 70, 70, 0xFFFF);
    tft.setCursor(102, 120);
    tft.print("Scan");

}



void loop()
{
    HorizontalMovement xMov = jcntr->getHorizontalMovement();
    VerticalMovement yMov = jcntr->getVerticalMovement();
    bool pushed = jcntr->getButtonPressed();
    bool changed = false;
    jcntr->clearButtonPressed();

    if (xMov == CENTER_LEFT && xPos == 1)
    {
        xPos = 0;
        oldX = 1;
        oldY = yPos;
        changed = true;
    }
    else if (xMov == CENTER_RIGHT && xPos == 0)
    {
        xPos = 1;
        oldX = 0;
        oldY = yPos;
        changed = true;
    }

    if (yMov == CENTER_UP && yPos == 1)
    {
        yPos = 0;
        oldY = 1;
        if (!changed)
            oldX = xPos;
        changed = true;
    }
    else if (yMov == CENTER_DOWN && yPos == 0)
    {
        yPos = 1;
        oldY = 0;
        if (!changed)
            oldX = xPos;
        changed = true;
    }

    if (pushed && grid[xPos][yPos])
    {
        if (laserOn)
        {
            laserOn = false;
            lcntr->turnOff();
            controller->runIdleMode();
        }
        else
        {
            laserOn = true;
            lcntr->turnOn();
            controller->runScanningMode();
        }
    }

    if (changed)
    {
        tft.fillRect(oldX * 80 + 11, oldY * 80 + 11, 68, 68, 0x0000);
    }

    if (laserOn)
    {
        tft.fillRect(90, 90, 70, 70, 0xF800);
    }

    tft.fillRect(xPos * 80 + 10, yPos * 80 + 10, 70, 70, 0xFFFF);
    tft.drawRect(10, 10, 70, 70, 0xFFFF);
    tft.drawRect(90, 10, 70, 70, 0xFFFF);
    tft.drawRect(10, 90, 70, 70, 0xFFFF);
    tft.drawRect(90, 90, 70, 70, 0xFFFF);

    

    tft.setCursor(102, 120);
    tft.print("Scan");

    Serial.print("X: ");
    Serial.println(xPos);
    Serial.print("Y: ");
    Serial.println(yPos);
    delay(50);
}