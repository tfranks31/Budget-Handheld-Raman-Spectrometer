#include <module_controllers/LEDController.hpp>

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

}

void LEDController::runScanningMode()
{

}

void LEDController::runErrorMode()
{

}

void LEDController::updateLED()
{

}