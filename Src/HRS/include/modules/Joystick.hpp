#pragma once

#include <IntervalTimer.h>
#include <stdint.h>

/**
 * How long to check if a button press was a bounce or not.
 */
#define BOUNCE_TIME 500 // us

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
     * Destructor for the joystick module.
     */
    ~Joystick();

    /**
     * Initialize the joystick module.
     */
    void init();

    /**
     * Get the joystick's x position.
     * @returns The x position of the joystick.
     */
    uint16_t getXPos();

    /**
     * Get the joystick's y position.
     * @returns The y position of the joystick.
     */
    uint16_t getYPos();

    /**
     * Get whether or not the button was pressed since the last clear.
     * @returns True if the button was pressed since the last clear, false if
     * not.
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
    static uint8_t buttonPinNum;

    /**
     * Whether or not the button was pressed since the last clear.
     */
    static bool wasButtonPressed;

    /**
     * Interval timer to detect bouncing on release of the button.
     */
    static IntervalTimer* timer;

    /**
     * Handles the button press interrupt and sets that the button was pressed.
     */
    static void handleButtonPress();

    /**
     * Confirm that the button press is correct.
     */
    static void confirmButtonPress();
};