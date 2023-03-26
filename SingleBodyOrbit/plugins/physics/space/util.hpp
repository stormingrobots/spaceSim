#pragma once

#include <cmath>

#include <plugins/physics.h>

// Physics Constants
const static double MU_EARTH = 3.9860442e14;

class vec3d {
  public:
  double x, y, z;

  vec3d() : x(0), y(0), z(0) {}
  vec3d(double x, double y, double z) : x(x), y(y), z(z) {}

  vec3d operator+(const vec3d& vec) const;
  vec3d operator-(const vec3d& vec) const;
  vec3d operator*(const double& scale) const;
  vec3d operator/(const double& scale) const;

  double norm() const;
  vec3d unit() const;
};

double clamp(const double val, const double minVal, const double maxVal);

#define log dWebotsConsolePrintf