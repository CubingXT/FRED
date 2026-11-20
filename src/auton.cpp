#include "main.h"
#include "fredlibx.h"

void autonomous() {
    while(inertialSensor.is_calibrating()) {
        pros::delay(2);
    }
    // move forward
	drive_straight(11.9);

    // turn
	turn_to_angle(-104);

    // raise arm first
    moveArm(-90, 300);

    // move to the post
	drive_straight(14);

    // move arm down
    moveArm(79, 320);   

    pros::delay(300);

    // try to open claw
    //openClaw();

    // go back up
    moveArm(-90, 100);
}
