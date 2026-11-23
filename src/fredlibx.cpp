#include "fredlibx.h"
#include "main.h" // IWYU pragma: keep
#include <cmath>

// Stops all motors on both sides of the drivetrain immediately
void brakeDrive() { 
    leftDrive.brake(); 
    rightDrive.brake(); 
}

void tareDrive() {
    leftDrive.tare_position_all();
    rightDrive.tare_position_all();
}

void drive_straight(double target_inches, int max_speed, int timeout_ms) {

    // Tuning constants (Proportional gains)
    constexpr double kP_drive = 0.5;   // Controls forward/backward speed based on remaining distance
    constexpr double kP_heading = 2.0; // Controls steering correction based on angle drift

    u_int32_t timestamp = pros::millis();
    
    // Reset motor encoders to 0 before starting
    tareDrive();

    // Lock onto the current heading to maintain a straight line
    double target_heading = inertialSensor.get_rotation();
    double target_degrees = (target_inches / (3.25 * M_PI)) * 360.0;;

    // Run control loop until the safety timeout expires
    while (pros::millis() - timestamp < timeout_ms) {
        // Average both sides to get total distance traveled
        double left_pos = leftDrive.get_position();
        double right_pos = rightDrive.get_position();
        double current_degrees = (left_pos + right_pos) / 2.0;

        // Calculate remaining distance to target
        double drive_error = target_degrees - current_degrees;

        // Exit loop early if within 5 degrees of the target
        if (std::abs(drive_error) < 5.0) break;

        // Calculate base forward power and clamp it within [-max_speed, max_speed]
        double forward_power = drive_error * kP_drive;
        if (forward_power > max_speed) forward_power = max_speed;
        if (forward_power < -max_speed) forward_power = -max_speed;

        // Calculate steering correction to stay aligned with initial heading
        double heading_error = target_heading - inertialSensor.get_rotation();
        double turn_correction = heading_error * kP_heading;

        // Apply combined forward power and heading correction to each side
        leftDrive.move(forward_power + turn_correction);
        rightDrive.move(forward_power - turn_correction);

        pros::delay(20); // Standard 20ms loop delay to save CPU resources
    }
    brakeDrive();
}

void turn_to_angle(double target_angle, int max_speed, int timeout_ms) {
    u_int32_t timestamp = pros::millis();
    
    // Reset motor encoders to 0 before starting
    tareDrive();

    // PD Tuning constants
    constexpr double kP = 1.8;  // Proportional gain: pushes toward target angle
    constexpr double kD = 0.15; // Derivative gain: dampens momentum to prevent overshooting

    double prev_error = target_angle - inertialSensor.get_rotation();
    int settle_time = 0; // Tracks how long the robot has stayed on target

    while (pros::millis() - timestamp < timeout_ms) {
        double current_angle = inertialSensor.get_rotation();
        double error = target_angle - current_angle;

        // Rate of change of error (used to slow down as robot approaches target)
        double derivative = error - prev_error;
        prev_error = error;

        // Check if within 1.5 degrees of target; require it to settle before exiting
        if (std::abs(error) < 1.5) {
            settle_time += 20;
            if (settle_time >= 100) break; // Exit once settled
        } else {
            settle_time = 0; // Reset timer if the robot overshoots or bounces out
        }

        // Calculate turn power and clamp within [-max_speed, max_speed]
        double turn_power = (error * kP) + (derivative * kD);
        if (turn_power > max_speed) turn_power = max_speed;
        if (turn_power < -max_speed) turn_power = -max_speed;

        // Spin left and right sides in opposite directions for a point turn
        leftDrive.move(turn_power);
        rightDrive.move(-turn_power);

        pros::delay(20);
    }
    brakeDrive();
}

/**
 * Moves the robot's arm motors for a fixed duration, compensating for 
 * mechanical differences when lifting upward.
 * 
 * @param speed Motor power (-127 to 127). Positive moves up, negative moves down.
 * @param time  Duration to run the motors in milliseconds.
 */
void moveArm(int speed, int time) {
    armLeft.move(speed);
    
    // If speed is positive (lifting), scale right motor to 70% to keep arm level;
    // otherwise (lowering), run both motors at full requested speed.
    if (std::abs(speed) == speed)
        armRight.move(speed * 0.7);
    else   
        armRight.move(speed);

    pros::delay(time);

    // Stop and hold arm position
    armLeft.brake();
    armRight.brake();
}
