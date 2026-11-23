#ifndef FRED_HPP
#define FRED_HPP

#include "api.h" // IWYU pragma: keep
#include "devices.h"
#include "ctrlr.hpp"

/**
 * @namespace fred
 * @brief Holds all functions and constant expressions that operate directly on the bot
 */

namespace fred {
    
    // Stops motors and holds their current position
    constexpr pros::MotorBrake HOLD = pros::MotorBrake::hold;

    // Gradually slows motors to a stop
    constexpr pros::MotorBrake COAST = pros::MotorBrake::coast;

    // Magic number for left motor
    constexpr double LEFT_MOTOR_NERF = 0.9;

    // Magic number for arm lowering
    constexpr double RIGHT_ARM_LOWER_NERF = 0.8;

    // Array of values for the gearshift
    constexpr std::array<double, 4> GEAR_MULTIPLES = {
        3.0,
        2.0,
        1.5,
        1.0
    };

    inline int gearLevel = 0;
    inline double gear = GEAR_MULTIPLES[gearLevel];

    // Decreases the gear
    inline void gearDown() {
        gearLevel--;
        if(gearLevel <= 0) gearLevel = 0;
        gear = GEAR_MULTIPLES[gearLevel];

        // Displays current gear to the user
        master.set_text(0, 0, "gear: " + std::to_string(gearLevel + 1));
    }

    // Increases the gear
    inline void gearUp() {
        gearLevel++;
        if (gearLevel >= 4) gearLevel = 3;
        gear = GEAR_MULTIPLES[gearLevel];

        // Displays current gear to the user
        master.set_text(0, 0, "gear: " + std::to_string(gearLevel + 1));
    }

    // Opens the pneumatic claw
    inline void openClaw() { claw.set_value(true); }

    // Closes the pneumatic claw
    inline void closeClaw() { claw.set_value(false); }

    // Moves wheels on robot based off of controller joysstick positions
    inline void updateDrive() {
        leftDrive.move(ctrlr::getStick(ctrlr::LS_Y) * LEFT_MOTOR_NERF / gear );
        rightDrive.move(ctrlr::getStick(ctrlr::RS_Y) / gear);
    }

    // Opens or closes claw
    inline void updateClaw() {
        if (ctrlr::pressed(ctrlr::L2)) closeClaw();
        if (ctrlr::pressed(ctrlr::R2)) openClaw();
    }

    // Controls arm
    inline void updateArm() {
        if (ctrlr::pressing(ctrlr::L1)) {
            armLeft.move(-127);
            armRight.move(-127);
        } else if (ctrlr::pressing(ctrlr::R1)) {
            armLeft.move(72);
            armRight.move(floor(72 * RIGHT_ARM_LOWER_NERF));
        } else {
            armLeft.brake();
            armRight.brake();
        }
    }

    // Changes gear up or down
    inline void updateGear() {
        if (ctrlr::pressed(ctrlr::DOWN)) gearDown();
        if (ctrlr::pressed(ctrlr::UP)) gearUp();
    }
}

#endif