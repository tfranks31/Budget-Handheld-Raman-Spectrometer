#pragma once

#include <IntervalTimer.h>
#include <modules/LED.hpp>
#include <stdint.h>

/**
 * The maximum brightness the LED will go to (0-255).
 */
#define MAX_BRIGHTNESS 20

/**
 * The time period between the groups of LED heartbeats.
 */
#define HEARTBEAT_LONG_RATE 5000000 // us

/**
 * The time period between the individual LED heartbeats.
 */
#define HEARTBEAT_SHORT_RATE 100000 // us

/**
 * How quickly to increment or decrement the LED brightness.
 */
#define FADE_RATE 500000    // us

/**
 * How quickly to toggle the LED when in error mode.
 */
#define TOGGLE_RATE 1000000 // us

/**
 * The maximum number of heartbeats in a group 
 * (Heartbeat is a single on and off flash).
 */
#define MAX_NUM_BEATS 2

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
     * If the LED is fading, whether or not to fade upwards
     */
    static bool fadeUp;

    /**
     * Track the number of heart beats
     */
    static uint8_t numBeats;

    /**
     * Make the LED flash like a heartbeat.
     */
    static void heartbeatLED();

    /**
     * Make the LED fade in and out.
     */
    static void fadeLED();

    /**
     * Toggle the LED state.
     */
    static void toggleLED();
};