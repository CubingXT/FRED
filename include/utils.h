#ifndef UTILS_H
#define UTILS_H

#include "devices.h"

// Opens the pneumatic claw
inline void openClaw() { claw.set_value(true); }

// Closes the pneumatic claw
inline void closeClaw() { claw.set_value(false); }

#endif