#pragma once

#include <cmath>

#include <plugins/physics.h>

double norm(const double* pos);
double clamp(const double val, const double minVal, const double maxVal);

#define log dWebotsConsolePrintf