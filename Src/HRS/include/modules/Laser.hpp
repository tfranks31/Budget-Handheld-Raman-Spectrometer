#pragma once

#include <stdint.h>

/**
 * Class for the laser used by the system.
 */
class Laser
{
public:

    /**
     * Constructor for the laser.
     * @param pinNum The pin number the laser is hooked up to.
     */
    Laser(uint8_t pinNum);

    /**
     * Initialize the laser.
     */
    void init();

    /**
     * Set the laser intensity.
     * @param intensity The intensity to set the laser to. 255 for max 
     * intensity, 0 for off.
     */
    void setIntensity(uint8_t intensity);

    /**
     * Turn the laser on.
     */
    void turnOn();

    /**
     * Turn the laser off.
     */
    void turnOff();

    /**
     * Get if the laser is turned on or not.
     * @returns True if the laser is on, false if it is not on.
     */
    bool getIsOn();

private:

    /**
     * The pin number that the laser is hooked up to.
     */
    uint8_t pinNum;

    /**
     * The set intensity of the laser. 255 for maximum brightness, 0 for off.
     */
    uint8_t intensity;

    /**
     * Whether or not the laser is on.
     */
    bool isOn;
};