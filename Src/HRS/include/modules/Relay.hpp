#pragma once

#include <stdint.h>

/**
 * Class for the relay module.
 */
class Relay
{
public:

    /**
     * Constructor for the relay module.
     * @param pinNum The pin number the relay module is hooked up to
     */
    Relay(uint8_t pinNum);

    /**
     * Initialize the relay module
     */
    void init();

    /**
     * Turn the relay module on (this allows current flow).
     */
    void turnOn();

    /**
     * Turn the relay module off (this stops current flow).
     */
    void turnOff();

    /**
     * Get whether or not the relay module is on or off.
     * @returns True is the relay is on, false if it is not.
     */
    bool getIsOn();

private:

    /**
     * Whether or not the relay is on or off. True is on, false is off.
     */
    bool isOn;

    /**
     * The pin number that the relay is hooked up to.
     */
    uint8_t pinNum;
};