#include "main.h"

void autonomous() {
    for (int i = 0; i < 4; i++) fred::gearDown();
    while(inertialSensor.is_calibrating()) { pros::delay(2); }

    // move forward
	drive_straight(12);

    // turn
	turn_to_angle(-104);

    // raise arm first
    moveArm(-90, 300);

    // move to the post
	drive_straight(20, 50);

    // move arm down
    moveArm(79, 320);   

    pros::delay(300);

    // try to open claw
    //fred::openClaw();

    // go back up
    moveArm(-90, 100);
}
