#ifndef DEVICES_H
#define DEVICES_H
#include "main.h"

extern pros::Controller master;
extern pros::Imu inertialSensor;
extern pros::adi::DigitalOut claw;
extern pros::Motor armLeft;
extern pros::Motor armRight;
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;

#endif