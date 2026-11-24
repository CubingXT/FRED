#ifndef DEVICES_H
#define DEVICES_H

#include "api.h" // IWYU pragma: keep

// Stops motors and holds their current position
constexpr pros::MotorBrake HOLD = pros::MotorBrake::hold;

// Gradually slows motors to a stop
constexpr pros::MotorBrake COAST = pros::MotorBrake::coast;

extern pros::Controller master;
extern pros::Imu inertialSensor;
extern pros::adi::DigitalOut claw;
extern pros::Motor armLeft;
extern pros::Motor armRight;
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;

#endif
