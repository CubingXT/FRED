#include "main.h"

double gear = 1.5;

void gearDown() {
	gear = 3;
	leftDrive.set_current_limit_all(1500);
	rightDrive.set_current_limit_all(1500);
}
void gearUp() {
	gear = 1.5;
	leftDrive.set_current_limit_all(2500);
	rightDrive.set_current_limit_all(2500);
}

void openClaw(){claw.set_value(true);}
void closeClaw(){claw.set_value(false);}

void initialize() {
	arm.set_brake_mode_all(pros::MotorBrake::hold);
	leftDrive.set_brake_mode_all(pros::MotorBrake::coast);
	rightDrive.set_brake_mode_all(pros::MotorBrake::coast);
	gearDown();
	inertialSensor.reset(true);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while (true) {
		// Drive
		leftDrive.move(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / gear);
		rightDrive.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / gear);

        // Claw
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) closeClaw();
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) openClaw();

        // Arm
		master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) ? arm.move(-63) :
		master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) ? arm.move(63) : arm.brake();

        // changeGear
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) gearDown();
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) gearUp();

		pros::delay(20);
	}
}

