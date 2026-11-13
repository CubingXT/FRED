#include "main.h"
#include <cmath>

double inches_to_degrees(double inches) {
    double wheel_diameter = 3.25;
    double gear_ratio = 1.0;
    double circumference = wheel_diameter * M_PI;
    
    return (inches / circumference) * 360.0 / gear_ratio;
}

/**
 * drive x inches
 * @param target_inches the amount of inches to move forward. Negitive numbers will move backwords
 * @param max_speed the maximum speed in percentage
 * @param timeout_ms the timeout for how long. setting to -1 is eq to 0 not inf
 */
void drive_straight(double target_inches, int max_speed, int timeout_ms) {
    drivetrain.tare_position_all();
    u_int32_t timestamp = pros::millis();
    double target_heading = inertialSensor.get_rotation();
    double target_degrees = inches_to_degrees(target_inches);

    // tuning
    double kP_drive = 0.5;
    double kP_heading = 2.0;

    while (pros::millis() - timestamp < timeout_ms) {
        double left_pos = leftDrive.get_position();
        double right_pos = rightDrive.get_position();
        double current_degrees = (left_pos + right_pos) / 2.0;

        double drive_error = target_degrees - current_degrees;

        if (std::abs(drive_error) < 5.0) break;

        double forward_power = drive_error * kP_drive;
        if (forward_power > max_speed) forward_power = max_speed;
        if (forward_power < -max_speed) forward_power = -max_speed;

        double heading_error = target_heading - inertialSensor.get_rotation();
        double turn_correction = heading_error * kP_heading;

        leftDrive.move(forward_power + turn_correction);
        rightDrive.move(forward_power - turn_correction);

        pros::delay(20);
    }

    drivetrain.brake();
}

/**
 * Turn x deg in any direction
 * @param target_angle Target angle relitive to current
 * @param max_speed the maximum speed in percentage
 * @param timeout_ms the timeout for how long. setting to -1 is eq to 0 not inf
 */
void turn_to_angle(double target_angle, int max_speed, int timeout_ms) {
    drivetrain.tare_position_all();
    u_int32_t timestamp = pros::millis();
    double kP = 1.8;
    double kD = 0.15;

    double prev_error = target_angle - inertialSensor.get_rotation();
    int settle_time = 0;

    while (pros::millis() - timestamp < timeout_ms) {
        double current_angle = inertialSensor.get_rotation();
        double error = target_angle - current_angle;

        double derivative = error - prev_error;
        prev_error = error;

        if (std::abs(error) < 1.5) {
            settle_time += 10;
            if (settle_time >= 100) break;
        } else settle_time = 0;

        double turn_power = (error * kP) + (derivative * kD);
        if (turn_power > max_speed) turn_power = max_speed;
        if (turn_power < -max_speed) turn_power = -max_speed;


        leftDrive.move(turn_power);
        rightDrive.move(-turn_power);

        pros::delay(20);
    }

    drivetrain.brake();
}
