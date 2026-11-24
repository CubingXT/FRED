#ifndef FRED_HPP
#define FRED_HPP

#include "devices.h"

/**
 * @namespace fred
 * @brief Holds all functions and constant expressions that operate directly on the bot
 */

namespace fred {

    // Opens the pneumatic claw
    inline void openClaw() { claw.set_value(true); }

    // Closes the pneumatic claw
    inline void closeClaw() { claw.set_value(false); }

    void gearUp();
    void gearDown();
    void updateDrive();
    void updateClaw();
    void updateArm();
    void updateGear();
}

#endif