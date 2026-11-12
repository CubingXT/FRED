#include "main.h"
#include "devices.hpp"

pros::Controller master (pros::E_CONTROLLER_MASTER);

pros::Imu inertialSensor (10);

pros::adi::DigitalOut claw('A');

// Arm
pros::MotorGroup arm (
	{-14, 16},
	pros::v5::MotorGears::red,
	pros::v5::MotorUnits::degrees
);

// Drivetrain
pros::MotorGroup leftDrive (
	{1, 8},
	pros::v5::MotorGears::blue,
	pros::v5::MotorUnits::degrees
);
pros::MotorGroup rightDrive (
	{-7, -5},
	pros::v5::MotorGears::blue,
	pros::v5::MotorUnits::degrees
);
pros::MotorGroup drivetrain (
    {1, 8, -7, -5},
    pros::v5::MotorGears::blue,
    pros::v5::MotorUnits::degrees
);