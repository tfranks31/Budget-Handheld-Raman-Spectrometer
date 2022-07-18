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
     * @param pinNum The pin number the relay module is hooked up to.
     */
    Relay(uint8_t pinNum);

    /**
     * Initialize the relay module.
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

private:

    /**
     * The pin number that the relay is hooked up to.
     */
    uint8_t pinNum;
};