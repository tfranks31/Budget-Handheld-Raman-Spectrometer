#pragma once

#include <stdint.h>

/**
 * Class for the joystick module. Also handles tracking joystick button presses.
 */
class Joystick
{
public:

    /**
     * Constructor for the joystick module.
     * @param xPinNum The pin number that the x analog is hooked up to.
     * @param yPinNum The pin number that the y analog is hooked up to.
     * @param buttonPinNum The pin number that the button is hooked up to.
     */
    Joystick(uint8_t xPinNum, uint8_t yPinNum, uint8_t buttonPinNum);

    /**
     * Initialize the joystick module.
     */
    void init();

    /**
     * Get the joystick's x position.
     */
    uint16_t getXPos();

    /**
     * Get the joystick's y position.
     */
    uint16_t getYPos();

    /**
     * Get whether or not the button was pressed since the last clear.
     */
    bool getButtonPressed();

    /**
     * Clear the state that the button was pressed. Used to reset the button.
     */
    void clearButtonPress();

private:

    /**
     * The pin number of the x analog is hooked up to.
     */
    uint8_t xPinNum;

    /**
     * The pin number that the y analog is hooked up to.
     */
    uint8_t yPinNum;

    /**
     * The pin number that the button is hooked up to.
     */
    uint8_t buttonPinNum;

    /**
     * Whether or not the button was pressed since the last clear
     */
    static bool wasButtonPressed;

    /**
     * Handles the button press interrupt and sets that the button was pressed
     */
    static void handleButtonPress();
};