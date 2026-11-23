#include "main.h" // IWYU pragma: keep
#include <array>
#include <string>

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

int gearLevel = 0;
double gear = GEAR_MULTIPLES[gearLevel];

// Decreases the gear
void fred::gearDown() {
    gearLevel--;
    if(gearLevel <= 0) gearLevel = 0;
    gear = GEAR_MULTIPLES[gearLevel];

    // Displays current gear to the user
    master.set_text(0, 0, "gear: " + std::to_string(gearLevel + 1));
}

// Increases the gear
void fred::gearUp() {
    gearLevel++;
    if (gearLevel >= 4) gearLevel = 3;
    gear = GEAR_MULTIPLES[gearLevel];

    // Displays current gear to the user
    master.set_text(0, 0, "gear: " + std::to_string(gearLevel + 1));
}

// Moves wheels on robot based off of controller joysstick positions
void fred::updateDrive() {
    leftDrive.move(ctrlr::getStick(ctrlr::LS_Y) * LEFT_MOTOR_NERF / gear );
    rightDrive.move(ctrlr::getStick(ctrlr::RS_Y) / gear);
}

// Opens or closes claw
void fred::updateClaw() {
    if (ctrlr::pressed(ctrlr::L2)) closeClaw();
    if (ctrlr::pressed(ctrlr::R2)) openClaw();
}

// Controls arm
void fred::updateArm() {
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
void fred::updateGear() {
    if (ctrlr::pressed(ctrlr::DOWN)) gearDown();
    if (ctrlr::pressed(ctrlr::UP)) gearUp();
}