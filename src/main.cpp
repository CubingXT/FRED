#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Devices

// Controller
controller Controller = controller();

// Sensors
inertial inertialSensor = inertial(PORT10, right);

// Motors

// Drivetrain motors
motor leftFrontMotor = motor(
    PORT1,
    ratio6_1,
    false
);
motor leftMiddleMotor = motor(
    PORT2,
    ratio6_1,
    false
);
motor leftBackMotor = motor(
    PORT3,
    ratio18_1,
    false
);
motor rightFrontMotor = motor(
    PORT4,
    ratio6_1,
    false
);
motor rightMiddleMotor = motor(
    PORT5,
    ratio6_1,
    false
);
motor rightBackMotor = motor(
    PORT6,
    ratio18_1,
    false
);

// Motor Groups
motor_group leftDrive = motor_group(
    leftFrontMotor,
    leftMiddleMotor,
    leftBackMotor
);
motor_group RightDrive = motor_group(
    rightFrontMotor,
    rightMiddleMotor,
    rightBackMotor
);

// Smartdrive
smartdrive smartDrivetrain = smartdrive (
    leftDrive,
    RightDrive,
    inertialSensor,
    260,
    431.8, // verify
    292.1,
    mm,
    1.0
);

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

    // Callibrate sensors
    inertialSensor.calibrate();
    while(inertialSensor.isCalibrating()) {
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
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
