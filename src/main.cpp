#include "main.h"
#include "namespaces.hpp"

constexpr pros::MotorBrake HOLD = pros::MotorBrake::hold;
constexpr pros::MotorBrake COAST = pros::MotorBrake::coast;

// Magic numbers
const double LEFT_MOTOR_NERF = 0.9;
const double RIGHT_ARM_LOWER_NERF = 0.8;

const int MAX_GEAR = 4;

const double GEAR_MULTIPLES[MAX_GEAR] = {
	3.0,
	2.0,
	1.5,
	1.0
};

int gearLevel = 0;
double gear = GEAR_MULTIPLES[gearLevel];

void gearDown() {
	gearLevel--;
	if(gearLevel <= 0) gearLevel = 0;

	gear = GEAR_MULTIPLES[gearLevel];

	master.set_text(0, 0, "gear: " + std::to_string(gearLevel + 1));
}
void gearUp() {
	gearLevel++;
	if(gearLevel >= MAX_GEAR) gearLevel = MAX_GEAR - 1;

	gear = GEAR_MULTIPLES[gearLevel];

	master.set_text(0, 0, "gear: " + std::to_string(gearLevel + 1));
}

void openClaw(){claw.set_value(true);}
void closeClaw(){claw.set_value(false);}

void initialize() {
	master.clear();
	pros::delay(50);	// So displays the gear bc controllers update every 50 msec
	leftDrive.set_brake_mode_all(COAST);
	rightDrive.set_brake_mode_all(COAST);
	armLeft.set_brake_mode(HOLD);
	armRight.set_brake_mode(HOLD);
	gearLevel = 0;
	gearDown();
	inertialSensor.reset(pros::competition::is_connected());
}

void disabled() {}

void competition_initialize() {}

void opcontrol() {
	while (true) {
		// Drive
		leftDrive.move(ctrlr::getStick(ctrlr::LS_Y) * LEFT_MOTOR_NERF / gear );
		rightDrive.move(ctrlr::getStick(ctrlr::RS_Y) / gear);

        // Claw
		if (ctrlr::pressed(ctrlr::L2)) closeClaw();
		if (ctrlr::pressed(ctrlr::R2)) openClaw();

        // Arm
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

        // changeGear
		if (ctrlr::pressed(ctrlr::DOWN)) gearDown();
		if (ctrlr::pressed(ctrlr::UP)) gearUp();

		pros::delay(20);
	}
}
