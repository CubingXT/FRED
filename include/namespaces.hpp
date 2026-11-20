#ifndef NAMESPACES_HPP
#define NAMESPACES_HPP

/**
 * This is a header library that simplifies the code.
 * @namespace ctrlr
 * @brief A namespace containing all controls and helper functions
          for the controller for easy readability.
*/

#include "api.h"
#include "devices.h"

// ALL CONTROLS ARE GONNA BE PLAYSTATION CONTROLS BC I CAN
namespace ctrlr {

    using Analog = pros::controller_analog_e_t;
    using Digital = pros::controller_digital_e_t;

    // Joysticks

    constexpr Analog RS_X = pros::E_CONTROLLER_ANALOG_RIGHT_X;
    constexpr Analog RS_Y = pros::E_CONTROLLER_ANALOG_RIGHT_Y;
    constexpr Analog LS_X = pros::E_CONTROLLER_ANALOG_LEFT_X;
    constexpr Analog LS_Y = pros::E_CONTROLLER_ANALOG_LEFT_Y;
    
    // Triggers

    constexpr Digital R1 = pros::E_CONTROLLER_DIGITAL_R1;
    constexpr Digital R2 = pros::E_CONTROLLER_DIGITAL_R2;
    constexpr Digital L1 = pros::E_CONTROLLER_DIGITAL_L1;
    constexpr Digital L2 = pros::E_CONTROLLER_DIGITAL_L2;

    // D-Pad

    constexpr Digital UP = pros::E_CONTROLLER_DIGITAL_UP;
    constexpr Digital DOWN = pros::E_CONTROLLER_DIGITAL_DOWN;
    constexpr Digital LEFT = pros::E_CONTROLLER_DIGITAL_LEFT;
    constexpr Digital RIGHT = pros::E_CONTROLLER_DIGITAL_RIGHT;

    // Face buttons
    
    constexpr Digital A = pros::E_CONTROLLER_DIGITAL_A;
    constexpr Digital B = pros::E_CONTROLLER_DIGITAL_B;
    constexpr Digital X = pros::E_CONTROLLER_DIGITAL_X;
    constexpr Digital Y = pros::E_CONTROLLER_DIGITAL_Y;

    // Helper functions

    inline bool pressed(pros::controller_digital_e_t button) { return master.get_digital_new_press(button); }
    inline bool pressing(pros::controller_digital_e_t button) { return master.get_digital(button); }
    inline int getStick(pros::controller_analog_e_t axis) { return master.get_analog(axis); }
}

#endif