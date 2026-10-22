#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Global variables
int gear;

// Devices

// Brain
brain Brain = brain();

// Controller
controller Controller = controller();

// Sensors
inertial inertialSensor = inertial(PORT10, right);
bumper goalSensor = bumper(Brain.ThreeWirePort.B);

// Pneumatics
pneumatics claw = pneumatics(Brain.ThreeWirePort.A);

// Motors

// Drivetrain motors
motor leftFrontMotor = motor (
    PORT1,
    ratio6_1,
    false
);
motor leftBackMotor = motor (
    PORT8,
    ratio6_1,
    false
);
motor rightFrontMotor = motor (
    PORT3,
    ratio6_1,
    true
);
motor rightBackMotor = motor (
    PORT5,
    ratio6_1,
    true
);

// Motor Groups
motor_group leftDrive = motor_group (
    leftFrontMotor,
    leftBackMotor
);
motor_group rightDrive = motor_group (
    rightFrontMotor,
    rightBackMotor
);

// Smartdrive
smartdrive smartDrivetrain = smartdrive (
    leftDrive,
    rightDrive,
    inertialSensor,
    260,
    429, // verify
    305,
    mm,
    1.0
);

// Artificial gearshift
void gearDown() {gear = 3;}
void gearUp() {gear = 1.5;}

// Claw
void openClaw() {claw.open();}
void closeClaw() {claw.close();}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

    // Set gear
    gear = 2;

    // Callibrate sensors
    inertialSensor.calibrate();
    while (inertialSensor.isCalibrating()) {
        wait(20, msec);
    }
    inertialSensor.resetHeading();
    inertialSensor.resetRotation();
    return;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
    // ..........................................................................
    // Insert autonomous user code here.
    // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
    gear = 3;
    leftDrive.setVelocity(0, percent);
    rightDrive.setVelocity(0, percent);
    // User control code here, inside the loop
    while (1) {

        // Movement
        leftDrive.spin(forward);
        rightDrive.spin(forward);
        leftDrive.setVelocity(Controller.Axis2.position() / gear * -1, percent);
        rightDrive.setVelocity(Controller.Axis3.position() / gear * -1, percent);

        // Claw
        Controller.ButtonR2.pressed(openClaw);
        Controller.ButtonR1.pressed(closeClaw);

        // Artificial gearshift
        Controller.ButtonDown.pressed(gearDown);
        Controller.ButtonUp.pressed(gearUp);
        wait(20, msec); // Sleep the task for a short amount of time to
                        // prevent wasted resources.
    }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
    }
}
