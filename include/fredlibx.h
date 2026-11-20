#ifndef FREDLIBX_H
#define FREDLIBX_H

void drive_straight(double target_inches, int max_speed = 50, int timeout_ms = 3000);

/**
 * drive x inches
 * @param target_inches the amount of inches to move forward. Negitive numbers will move backwords
 * @param max_speed the maximum speed in percentage
 * @param timeout_ms the timeout for how long. setting to -1 is eq to 0 not inf
 */

void turn_to_angle(double target_degrees, int max_speed = 50, int timeout_ms = 2000);

/**
 * Turn x deg in any direction
 * @param target_degrees Target angle relitive to current
 * @param max_speed the maximum speed in percentage
 * @param timeout_ms the timeout for how long. setting to -1 is eq to 0 not inf
 */

void moveArm(int speed, int time);

/**
 * Move arm up or down
 * @param speed The speed at which the arm moves
 * @param time How long the arm moves
 */

#endif
