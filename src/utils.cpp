#include "main.h"

void gearDown() {
	gear = 3;
	drivetrain.set_current_limit_all(1500);
}
void gearUp() {
	gear = 1.5;
	drivetrain.set_current_limit_all(2500);
}

void openClaw(){claw.set_value(true);}
void closeClaw(){claw.set_value(false);}