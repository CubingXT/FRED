#ifndef GLOBALS_H
#define GLOBALS_H

void drive_straight(double target_inches, int max_speed = 50, int timeout_ms = 3000);
void turn_to_angle(double target_degrees, int max_speed = 50, int timeout_ms = 2000);

#endif