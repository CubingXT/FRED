#include "main.h"


#define maxGear 4
#define leftMotorNerf 0.9
const double gearMultiples[maxGear] = {
	3.0,
	2.0,
	1.5,
	1.0
};
int gearLevel = 0;
double gear = gearMultiples[gearLevel];



void gearDown() {
	gearLevel--;
	if(gearLevel <= 0) {
		gearLevel = 0;
	}

	gear = gearMultiples[gearLevel];

	master.set_text(0, 0, "gear: " + std::to_string(gearLevel + 1));
}
void gearUp() {
	gearLevel++;
	if(gearLevel >= maxGear) {
		gearLevel = maxGear - 1;
	}

	gear = gearMultiples[gearLevel];

	master.set_text(0, 0, "gear: " + std::to_string(gearLevel + 1));
}

void openClaw(){claw.set_value(true);}
void closeClaw(){claw.set_value(false);}

void initialize() {
	master.clear();
	arm.set_brake_mode_all(pros::MotorBrake::hold);
	leftDrive.set_brake_mode_all(pros::MotorBrake::coast);
	rightDrive.set_brake_mode_all(pros::MotorBrake::coast);
	gearLevel = 0;
	gearDown();
	inertialSensor.reset(pros::competition::is_connected());
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	double rightArmTrack = 0;
	double leftArmTrack = 0;
	while (true) {
		// Drive
		leftDrive.move(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * leftMotorNerf / gear );
		rightDrive.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / gear);

        // Claw
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) closeClaw();
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) openClaw();

        // Arm
		master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) ? arm.move(-127) :
		master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) ? arm.move(50) : arm.brake();

        // changeGear
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) gearDown();
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) gearUp();

		pros::delay(20);
	}
}

