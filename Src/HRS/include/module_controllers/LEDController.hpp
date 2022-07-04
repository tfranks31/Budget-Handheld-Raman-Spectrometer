#pragma once

#include <modules/LED.hpp>
#include <stdint.h>
#include <IntervalTimer.h>

#define MAX_BRIGHTNESS 100

/**
 * Different LED modes that correspond with different LED patterns.
 */
enum LEDMode
{
    Off,
    Idle,
    ScanHigh,
    ScanLow,
    Error
};

/**
 * Class used to control the status LED on the system.
 */
class LEDController
{
public:

    /**
     * Constructor for the LEDController.
     */
    LEDController(uint8_t pinNum);

    /**
     * Destructor for the LEDController.
     */
    ~LEDController();

    /**
     * Bring the LED module online.
     */
    void bringOnline();

    /**
     * Bring the LED module offline.
     */
    void bringOffline();

    /**
     * Put the LED module into idle mode. This produces a heartbeat pattern.
     * The LED should be in this mode whenever the system is not scanning.
     */
    void runIdleMode();

    /**
     * Put the LED module into scanning mode. This produces a fading pattern.
     * The LED should be in this mode whenever the system is scanning.
     */
    void runScanningMode();

    /**
     * Put the LED module into error mode. This produces a flashing pattern.
     * The LED should be in this mode whenever the system has errored.
     */
    void runErrorMode();

private:

    /**
     * The system's status LED.
     */
    LED* statusLED;

    /**
     * The interval timer used to implement LED modes.
     */
    IntervalTimer* timer;

    /**
     * The mode that the LED is being commanded with.
     */
    LEDMode mode;

    /**
     * Update the LED based on the selected mode. Used by the timer. 
     */
    void updateLED();
};