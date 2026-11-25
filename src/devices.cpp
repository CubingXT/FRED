#include "main.h" // IWYU pragma: keep

pros::v5::Controller master(pros::E_CONTROLLER_MASTER);

pros::v5::Imu inertialSensor(10);

pros::adi::DigitalOut claw('A');

// Arm
pros::v5::Motor armLeft(-14);
pros::v5::Motor armRight(16);

// Drivetrain
pros::v5::MotorGroup leftDrive (
	{1, 8},
	pros::v5::MotorGears::blue,
	pros::v5::MotorUnits::degrees
);
pros::v5::MotorGroup rightDrive(
	{-7, -5},
	pros::v5::MotorGears::blue,
	pros::v5::MotorUnits::degrees
);