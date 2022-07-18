#pragma once

#include <stdint.h>
#include <modules/Relay.hpp>

class RelayController
{
public:

    /**
     * Constructor for the relay controller.
     * @param pinNum The pin number the relay module is hooked up to.
     */
    RelayController(uint8_t pinNum);
    
    /**
     * Destructor for the relay controller
     */
    ~RelayController();

    /**
     * Bring the relay module online.
     */
    void bringOnline();

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
     * The relay module.
     */
    Relay* relay;
};