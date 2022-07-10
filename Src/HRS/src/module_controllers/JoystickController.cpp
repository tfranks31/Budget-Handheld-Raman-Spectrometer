#include <module_controllers/JoystickController.hpp>

JoystickController::JoystickController(uint8_t xPinNum, uint8_t yPinNum, 
                                        uint8_t buttonPinNum)
{
    joystick = new Joystick(xPinNum, yPinNum, buttonPinNum);
    previousX = CENTER;
    previousY = CENTER;
}

JoystickController::~JoystickController()
{
    delete joystick;
}

void JoystickController::bringOnline()
{
    joystick->init();
}

HorizontalMovement JoystickController::getHorizontalMovement()
{
    uint16_t currentX = joystick->getXPos();
    HorizontalMovement result;

    // Check each of the previousX states to determine the movement
    if (previousX == CENTER)
    {
        // Moved from Center to Left
        if (currentX > CENTER_UPPER_THRESHOLD)
        {
            result = CENTER_LEFT;
            previousX = UPPER;
        }
        // Moved from Center to Right
        else if (currentX < CENTER_LOWER_THRESHOLD)
        {
            result = CENTER_RIGHT;
            previousX = LOWER;
        }
        // Stayed in the Center
        else
        {
            result = CENTER_CENTER_H;
        }
    }
    else if (previousX == UPPER)
    {
        // Moved from Left to Right
        if (currentX < UPPER_LOWER_THRESHOLD) 
        {
            result = LEFT_RIGHT;
            // Determine how far moved to determine next state
            previousX = (currentX < CENTER_LOWER_THRESHOLD) ? LOWER : CENTER;
        }
        // Stayed at Right
        else
        {
            result = LEFT_LEFT;
        }
    }
    else    // previousX == LOWER
    {
        // Moved from Left to Right
        if (currentX > LOWER_UPPER_THRESHOLD) 
        {
            result = RIGHT_LEFT;
            // Determine how far moved to determine next state
            previousX = (currentX > CENTER_UPPER_THRESHOLD) ? UPPER : CENTER;
        }
        // Stayed at Left
        else
        {
            result = RIGHT_RIGHT;
        }
    }

    return result;
}

VerticalMovement JoystickController::getVerticalMovement()
{
    uint16_t currentY = joystick->getYPos();
    VerticalMovement result;

    // Check each of the previousY states to determine the movement
    if (previousY == CENTER)
    {
        // Moved from the Center to Down
        if (currentY > CENTER_UPPER_THRESHOLD)
        {
            result = CENTER_UP;
            previousY = UPPER;
        }
        // Moved from the Center to UP
        else if (currentY < CENTER_LOWER_THRESHOLD)
        {
            result = CENTER_DOWN;
            previousY = LOWER;
        }
        // Stayed at the Center
        else
        {
            result = CENTER_CENTER_V;
        }
    }
    else if (previousY == UPPER)
    {
        // Moved from Down to Up
        if (currentY < UPPER_LOWER_THRESHOLD) 
        {
            result = UP_DOWN;
            // Determine how far moved to determine next state
            previousY = (currentY < CENTER_LOWER_THRESHOLD) ? LOWER : CENTER;
        }
        // Stayed Down
        else
        {
            result = UP_UP;
        }
    }
    else    // previousX == LOWER
    {
        // Moved from Up to Down
        if (currentY > LOWER_UPPER_THRESHOLD) 
        {
            result = DOWN_UP;
            // Determine how far moved to determine next state
            previousY = (currentY > CENTER_UPPER_THRESHOLD) ? UPPER : CENTER;
        }
        // Stayed Up
        else
        {
            result = DOWN_DOWN;
        }
    }

    return result;
}

bool JoystickController::getButtonPressed()
{
    return joystick->getButtonPressed();
}

void JoystickController::clearButtonPressed()
{
    joystick->clearButtonPress();
}