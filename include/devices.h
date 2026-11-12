#ifndef DEVICES_HPP
#define DEVICES_HPP
#include "main.h"

extern pros::Controller master;
extern pros::Imu inertialSensor;
extern pros::adi::DigitalOut claw;
extern pros::MotorGroup arm;
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;
extern pros::MotorGroup drivetrain;

#endif