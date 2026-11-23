#include "main.h" 

// Stops motors and holds their current position
constexpr pros::MotorBrake HOLD = pros::MotorBrake::hold;

// Gradually slows motors to a stop
constexpr pros::MotorBrake COAST = pros::MotorBrake::coast;

// Reset robot
void initialize() {
	master.clear();
	pros::delay(50);	// So displays the gear bc controllers update every 50 msec

	leftDrive.set_brake_mode_all(COAST);
	rightDrive.set_brake_mode_all(COAST);
	armLeft.set_brake_mode(HOLD);
	armRight.set_brake_mode(HOLD);

	fred::gearDown();
	inertialSensor.reset(pros::competition::is_connected());
}

void disabled() {}

void competition_initialize() {}

// User control
void opcontrol() {
	while (true) {
		fred::updateDrive();
		fred::updateClaw();
		fred::updateArm();
		fred::updateGear();
		pros::delay(20);
	}
}
