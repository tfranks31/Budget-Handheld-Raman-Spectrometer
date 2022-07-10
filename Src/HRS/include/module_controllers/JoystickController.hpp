#pragma once

#include <modules/Joystick.hpp>
#include <stdint.h>

/**
 * The maximum joystick value. 0 will always be the minimum.
 */
#define MAX_READING 1023

/**
 * The value for when a joystick axis is crossing from center to upper range.
 */
#define CENTER_UPPER_THRESHOLD (MAX_READING * 5) / 6

/**
 * The value for when a joystick axis is crossing from center to lower range.
 */
#define CENTER_LOWER_THRESHOLD (MAX_READING * 1) / 6

/**
 * The value for when a joystick axis is crossing from upper to center/lower
 * range.
 */
#define UPPER_LOWER_THRESHOLD (MAX_READING * 4) / 6

/**
 * The value for when a joystick axis is crossing from lower to center/upper
 * range.
 */
#define LOWER_UPPER_THRESHOLD (MAX_READING * 2) / 6

/**
 * The different horizontal movements performed by the joystick. The first word
 * is the position that the joystick was at initially before the read. The
 * second word is the position that was read. A movement from left to right or
 * left to center are synonymous since both will produce the same behavior. Same
 * with right to left.
 */
enum HorizontalMovement
{
    LEFT_LEFT,
    LEFT_RIGHT,
    CENTER_LEFT,
    CENTER_CENTER_H,
    CENTER_RIGHT,
    RIGHT_LEFT,
    RIGHT_RIGHT
};

/**
 * The different vertical movements performed by the joystick. The first word is
 * the position that the joystick was at initially before the read. The second 
 * word is the position that was read. A movement from up to down or up to
 * center are synonymous since both will produce the same behavior. Same with 
 * down to up.
 */
enum VerticalMovement
{
    UP_UP,
    UP_DOWN,
    CENTER_UP,
    CENTER_CENTER_V,
    CENTER_DOWN,
    DOWN_UP,
    DOWN_DOWN
};

/**
 * Different joystick positions. Used as states for where a joystick is along
 * its axes.
 */
enum Position
{
    UPPER,
    CENTER,
    LOWER
};

/**
 * The controller class for the joystick module. Use to monitor the joystick.
 */
class JoystickController
{
public:

    /**
     * Constructor for the joystick controller.
     * @param xPinNum The pin number that the x analog is hooked up to.
     * @param yPinNum The pin number that the y analog is hooked up to.
     * @param buttonPinNum The pin number that the button is hooked up to.
     */
    JoystickController(uint8_t xPinNum, uint8_t yPinNum, uint8_t buttonPinNum);

    /**
     * Destructor for the joystick controller.
     */
    ~JoystickController();

    /**
     * Bring the joystick module online.
     */
    void bringOnline();

    /**
     * Get the horizontal movement that was last performed by the joystick.
     * @returns The horizontal movement last performed by the joystick.
     */
    HorizontalMovement getHorizontalMovement();

    /**
     * Get the vertical movement that was last performed by the joystick.
     * @returns The vertical movment last performed by the joystick.
     */
    VerticalMovement getVerticalMovement();

    /**
     * Get whether or not the button was recently clicked.
     * @returns True if the button was pressed, false if not.
     */
    bool getButtonPressed();

    /**
     * Clear the button press. Used to see if the button gets clicked again.
     */
    void clearButtonPressed();

private:

    /**
     * The joystick module used by the system.
     */
    Joystick* joystick;

    /**
     * The previous analog X position, used for determining movements.
     */
    Position previousX;

    /**
     * The previous analog Y position, used for determining movements.
     */
    Position previousY;
};