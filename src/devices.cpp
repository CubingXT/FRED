#include "main.h"

pros::Controller master (pros::E_CONTROLLER_MASTER);

pros::Imu inertialSensor (10);

pros::adi::DigitalOut claw('A');

// Arm
pros::Motor armLeft ( -14);
pros::Motor armRight(16);

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