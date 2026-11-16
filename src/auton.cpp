#include "main.h"
#include <math.h>

void moveClaw(int speed, int time) {
    armLeft.move(speed);
    if(std::abs(speed) == speed)
        armRight.move(speed * 0.7);
    else   
        armRight.move(speed);

    pros::delay(time);

    armLeft.brake();
    armRight.brake();
}

void autonomous() {
	inertialSensor.reset(true);
    while(inertialSensor.is_calibrating()) {
        pros::delay(2);
    }
    // move forward
	drive_straight(11.9);

    // turn
	turn_to_angle(-104);

    // raise arm first
    moveClaw(-90, 300);

    // move to the post
	drive_straight(14);

    // move arm down
    moveClaw(79, 320);   

    pros::delay(300);

    // try to open claw
    //openClaw();

    // go back up
    moveClaw(-90, 100);
}
