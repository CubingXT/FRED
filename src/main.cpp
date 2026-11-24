#include "main.h" 

// Reset robot
void initialize() {
	ctrlr::clear();
	pros::delay(50);	// So displays the gear bc controllers update every 50 msec

	leftDrive.set_brake_mode_all(COAST);
	rightDrive.set_brake_mode_all(COAST);
	armLeft.set_brake_mode(HOLD);
	armRight.set_brake_mode(HOLD);

	for (int i = 0; i < 4; i++) fred::gearDown();
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
