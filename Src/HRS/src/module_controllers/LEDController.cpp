#include <module_controllers/LEDController.hpp>

LED* LEDController::statusLED;
IntervalTimer* LEDController::timer;
LEDMode LEDController::mode;
bool LEDController::fadeUp;
bool LEDController::longPause;
uint8_t LEDController::numBeats;

LEDController::LEDController(uint8_t pinNum)
{
    statusLED = new LED(pinNum);
    timer = new IntervalTimer();
    mode = Off;
}

LEDController::~LEDController()
{
    bringOffline();
    delete timer;
    delete statusLED;
}

void LEDController::bringOnline()
{
    statusLED->init();
    statusLED->setBrightness(MAX_BRIGHTNESS);
    runIdleMode();  
}

void LEDController::bringOffline()
{
    timer->end();
    statusLED->turnOff();
    mode = Off;
}

void LEDController::runIdleMode()
{
    timer->begin(updateLED, HEARTBEAT_LONG_TIMEOUT);
    
    // Set mode after timer begin. If it was before, the timer could interupt
    // after, causing undefined behavior
    statusLED->setBrightness(MAX_BRIGHTNESS);
    longPause = true;
    mode = Idle;
}

void LEDController::runScanningMode()
{
    timer->begin(updateLED, FADE_RATE);
    statusLED->setBrightness(0);
    statusLED->turnOn();
    fadeUp = true;
    mode = Scan;
}

void LEDController::runErrorMode()
{
    timer->begin(updateLED, ERROR_TOGGLE);
    statusLED->setBrightness(MAX_BRIGHTNESS);
    mode = Error;
}

void LEDController::updateLED()
{
    switch (mode)
    {
        case Idle:
            if (longPause)
            {
                timer->begin(updateLED, HEARTBEAT_SHORT_TIMEOUT);
                statusLED->turnOn();
                longPause = false;
                numBeats = 1;
            }
            else
            {
                if (statusLED->getIsOn())
                {
                    statusLED->turnOff();
                    if (numBeats >= MAX_NUM_BEATS)
                    {
                        timer->begin(updateLED, HEARTBEAT_LONG_TIMEOUT);
                        longPause = true;
                    }
                }
                else
                {
                    statusLED->turnOn();
                    numBeats++;
                }
            }
            break;
        case Scan:
            if (fadeUp)
            {
                uint8_t newBrightness = statusLED->getBrightness() + 1;
                statusLED->setBrightness(newBrightness);
                if (newBrightness >= MAX_BRIGHTNESS)
                {
                    fadeUp = false;
                }
            }
            else
            {
                uint8_t newBrightness = statusLED->getBrightness() - 1;
                statusLED->setBrightness(newBrightness);
                if (newBrightness <= 0)
                {
                    fadeUp = true;
                }
            }
            break;
        case Error:
            if (statusLED->getIsOn())
            {
                statusLED->turnOff();
            }
            else
            {
                statusLED->turnOn();
            }
            break;
        //default:
    };
}