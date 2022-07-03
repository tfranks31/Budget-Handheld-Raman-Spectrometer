#pragma once

#include <modules/LED.hpp>
#include <stdint.h>

/**
 * Class used to control the status LED on the system.
 */
class LEDController
{
public:

    /**
     * Constructor for the LEDController.
     */
    LEDController();

    /**
     * Bring the LED module online.
     */
    void bringOnline();

    /**
     * Bring the LED module offline
     */ 
    void bringDown();

    /**
     * Put the LED module into idle mode. This produces a heartbeat pattern.
     * The LED should be in this mode whenever the system is not scanning.
     */ 
    void idleMode();

    /**
     * Put the LED module into scanning mode. This produces a fading pattern.
     * The LED should be in this mode whenever the system is scanning.
     */ 
    void scanningMode();

    /**
     * Put the LED module into error mode. This produces a flashing pattern.
     * The LED should be in this mode whenever the system has errored.
     */ 
    void errorMode();

private:

    /**
     * The system's status LED.
     */ 
    LED* statusLED; 
};