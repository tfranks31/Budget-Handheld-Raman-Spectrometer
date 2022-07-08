#include <module_controllers/LEDController.hpp>

// NOTE: Static variables and functions had to be used in order to interact with
// them in the timer ISR. 
/**
 * The system's status LED.
 */
LED* LEDController::statusLED;

/**
 * The interval timer used to implement LED modes.
 */
IntervalTimer* LEDController::timer;

/**
 * If the LED is fading, whether or not to fade upwards
 */
bool LEDController::fadeUp;

/**
 * Track the number of heart beats
 */
uint8_t LEDController::numBeats;

LEDController::LEDController(uint8_t pinNum)
{
    statusLED = new LED(pinNum);
    timer = new IntervalTimer();
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
}

void LEDController::runIdleMode()
{
    // Set up and run the LED in heartbeat mode
    timer->begin(heartbeatLED, HEARTBEAT_LONG_RATE);
    statusLED->setBrightness(MAX_BRIGHTNESS);
    statusLED->turnOff();
    numBeats = 0;
}

void LEDController::runScanningMode()
{
    // Set up and run the LED in fade mode
    timer->begin(fadeLED, FADE_RATE);
    statusLED->setBrightness(0);
    statusLED->turnOn();
    fadeUp = true;
}

void LEDController::runErrorMode()
{
    // Error mode is just toggling the LED
    timer->begin(toggleLED, TOGGLE_RATE);
    statusLED->setBrightness(MAX_BRIGHTNESS);
}

void LEDController::heartbeatLED()
{
    // We use the number of "beats" to track how many times the LED state has
    // changed. The LED will be toggled for ever timer iteration, with the
    // difference being how long until the next LED toggle.
    if ((numBeats + 1) / 2 == MAX_NUM_BEATS)
    {
        // We finished our heartbeat(s), reset and wait a for the next beats
        timer->begin(heartbeatLED, HEARTBEAT_LONG_RATE);
        numBeats = 0;
    }
    else
    {
        // We just started the next series of beats, set the timer short and
        // start beating
        if (numBeats == 0)
        {
            timer->begin(heartbeatLED, HEARTBEAT_SHORT_RATE);
        }
        numBeats++;
    }
    toggleLED();
}

void LEDController::fadeLED()
{
    // Increase brightness if we are fading up
    if (fadeUp)
    {
        uint8_t newBrightness = statusLED->getBrightness() + 1;
        statusLED->setBrightness(newBrightness);

        // We reached the maximum brightness, start fading down
        if (newBrightness == MAX_BRIGHTNESS)
        {
            fadeUp = false;
        }
    }
    // Decrease brightness if we are fading down
    else
    {
        uint8_t newBrightness = statusLED->getBrightness() - 1;
        statusLED->setBrightness(newBrightness);
        
        // We reached the lowest brightness, start fading up
        if (newBrightness == 0)
        {
            fadeUp = true;
        }
    }
}

void LEDController::toggleLED()
{
    statusLED->getIsOn() ? statusLED->turnOff() : statusLED->turnOn();
}