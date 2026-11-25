#ifndef DEVICES_H
#define DEVICES_H

#include "api.h" // IWYU pragma: keep

// Stops motors and holds their current position
constexpr pros::v5::MotorBrake HOLD = pros::v5::MotorBrake::hold;

// Gradually slows motors to a stop
constexpr pros::v5::MotorBrake COAST = pros::v5::MotorBrake::coast;

extern pros::v5::Controller master;
extern pros::v5::Imu inertialSensor;
extern pros::adi::DigitalOut claw;
extern pros::v5::Motor armLeft;
extern pros::v5::Motor armRight;
extern pros::v5::MotorGroup leftDrive;
extern pros::v5::MotorGroup rightDrive;

#endif
