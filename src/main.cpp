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

// Arm motors
motor rightArmMotor1 = motor (
    PORT14,
    ratio36_1,
    true
);
motor rightArmMotor2 = motor (
    PORT11,
    ratio36_1,
    false
);

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
motor_group arm = motor_group(
    rightArmMotor1,
    rightArmMotor2
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
void gearDown(){gear = 3;}
void gearUp(){gear = 1.5;}

// Claw
void openClaw(){claw.open();}
void closeClaw(){claw.close();}

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

    // Set screen
    Controller.Screen.clearScreen();

    // Set gear
    gear = 2;

    // Callibrate sensors
    inertialSensor.calibrate();
    while (inertialSensor.isCalibrating()){wait(20, msec);}
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
    auto armVelocity = 0;
    gear = 3;
    leftDrive.setVelocity(0, percent);
    rightDrive.setVelocity(0, percent);
    arm.setVelocity(0, percent);
    leftDrive.spin(forward);
    rightDrive.spin(forward);
    arm.spin(forward);
    // User control code here, inside the loop
    while (1) {

        // Movement
        auto turn = Controller.Axis1.position();
        auto forward = Controller.Axis2.position() * -1;

        leftDrive.setVelocity((turn + forward) / gear, percent);
        rightDrive.setVelocity((forward - turn) / gear, percent);

        // Claw
        Controller.ButtonR2.pressed(openClaw);
        Controller.ButtonL2.pressed(closeClaw);

        // Arm
        if (Controller.ButtonL1.pressing()) {
            armVelocity = -100;
        } else if (Controller.ButtonR1.pressing()) {
            armVelocity = 100;
        } else {
            armVelocity = 0;
        }

        arm.setVelocity(armVelocity, percent);

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
