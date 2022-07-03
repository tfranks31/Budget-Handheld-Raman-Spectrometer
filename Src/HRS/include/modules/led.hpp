#pragma once

#include <stdint.h>

/**
 * Class for the status led used by the system.
 */
class Led
{
public:

    /**
     * Constructor for the LED.
     * @param pinNum The pin number the LED is hooked up to.
     */
    void led(uint8_t pinNum);

    /**
     * Initialize the LED.
     */
    void init();

    /**
     * Set the LED brightness.
     * @param brightness The brightness to set the LED to. 255 for max brighness, 0 for off.
     */
    void setBrightness(uint8_t brightness);

    /**
     * Turn the LED on.
     */
    void turnOn();

    /**
     * Turn the LED off.
     */
    void turnOff();

    /**
     * Get if the LED is turned on or not.
     * @returns True if the LED is on, false if it is not on.
     */
    bool getIsOn();

private:

    /**
     * The pin number that the LED is hooked up to.
     */
    uint8_t pinNum;

    /**
     * The set brightness of the LED. 255 for maximum brightness, 0 for off.
     */
    uint8_t brightness;

    /**
     * Whether or not the LED is on.
     */
    bool isOn;
};