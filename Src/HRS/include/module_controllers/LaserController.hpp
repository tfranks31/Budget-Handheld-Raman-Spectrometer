#pragma once

#include <stdint.h>
#include <modules/Laser.hpp>

/**
 * Class used to control the laser of the system. 
 */
class LaserController
{
public:

    /**
     * Constructor for the LaserController.
     * @param pinNum The pin number the laser is hooked up to.
     */
    LaserController(uint8_t pinNum);

    /**
     * Destructor for the LaserController.
     */
    ~LaserController();

    /**
     * Bring the laser online.
     */
    void bringOnline();

    /**
     * Bring the laser offline.
     */
    void bringOffline();

    /**
     * Turn on the laser.
     */
    void turnOn();

    /**
     * Turn off the laser.
     */
    void turnOff();

    /**
     * Set the intensity of light for when the laser is turned on.
     * @param scanIntensity The intensity of the laser light (0-255).
     */
    void setIntensity(uint8_t scanIntensity);

private:

    /**
     * The laser used for scanning.
     */
    Laser* laser;
};