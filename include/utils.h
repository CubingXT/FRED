#ifndef UTILS_H
#define UTILS_H

#include "main.h"

void drive_straight(double target_inches, int max_speed = 50, int timeout_ms = 3000);
void turn_to_angle(double target_degrees, int max_speed = 50, int timeout_ms = 2000);

inline double gear = 3;
void gearUp();
void gearDown();

void openClaw();
void closeClaw();

#endif