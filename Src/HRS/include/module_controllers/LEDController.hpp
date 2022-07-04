#pragma once

#include <modules/LED.hpp>
#include <stdint.h>
#include <IntervalTimer.h>

#define MAX_BRIGHTNESS 20
#define HEARTBEAT_LONG_TIMEOUT 5000000
#define HEARTBEAT_SHORT_TIMEOUT 100000
#define MAX_NUM_BEATS 2
#define FADE_RATE 50000
#define ERROR_TOGGLE 1000000

/**
 * Different LED modes that correspond with different LED patterns.
 */
enum LEDMode
{
    Off,
    Idle,
    Scan,
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
    static LED* statusLED;

    /**
     * The interval timer used to implement LED modes.
     */
    static IntervalTimer* timer;

    /**
     * The mode that the LED is being commanded with.
     */
    static LEDMode mode;

    /**
     * If the LED is fading, whether or not to fade upwards
     */
    static bool fadeUp;

    /**
     * If the LED is doing a heart beat, whether or not 
     */
    static bool longPause;

    /**
     * Track the number of heart beats
     */
    static uint8_t numBeats;

    /**
     * Update the LED based on the selected mode. Used by the timer. 
     */
    static void updateLED();
};