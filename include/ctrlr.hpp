#ifndef CTRLR_HPP
#define CTRLR_HPP

/**
 * @namespace ctrlr
 * @brief A namespace containing all controls and helper functions for the controller for easy readability.
*/

#include "devices.h"

// Buttons on controller
namespace ctrlr {

    using namespace pros;
    using Analog = controller_analog_e_t;
    using Digital = controller_digital_e_t;

    // Joysticks

    constexpr Analog RS_X = E_CONTROLLER_ANALOG_RIGHT_X;
    constexpr Analog RS_Y = E_CONTROLLER_ANALOG_RIGHT_Y;
    constexpr Analog LS_X = E_CONTROLLER_ANALOG_LEFT_X;
    constexpr Analog LS_Y = E_CONTROLLER_ANALOG_LEFT_Y;
    
    // Triggers

    constexpr Digital R1 = E_CONTROLLER_DIGITAL_R1;
    constexpr Digital R2 = E_CONTROLLER_DIGITAL_R2;
    constexpr Digital L1 = E_CONTROLLER_DIGITAL_L1;
    constexpr Digital L2 = E_CONTROLLER_DIGITAL_L2;

    // D-Pad

    constexpr Digital UP = E_CONTROLLER_DIGITAL_UP;
    constexpr Digital DOWN = E_CONTROLLER_DIGITAL_DOWN;
    constexpr Digital LEFT = E_CONTROLLER_DIGITAL_LEFT;
    constexpr Digital RIGHT = E_CONTROLLER_DIGITAL_RIGHT;

    // Face buttons
    
    constexpr Digital A = E_CONTROLLER_DIGITAL_A;
    constexpr Digital B = E_CONTROLLER_DIGITAL_B;
    constexpr Digital X = E_CONTROLLER_DIGITAL_X;
    constexpr Digital Y = E_CONTROLLER_DIGITAL_Y;

    // Helper functions

    inline bool pressed(Digital button) { return master.get_digital_new_press(button); }
    inline bool pressing(Digital button) { return master.get_digital(button); }
    inline int getStick(Analog axis) { return master.get_analog(axis); }
}

#endif