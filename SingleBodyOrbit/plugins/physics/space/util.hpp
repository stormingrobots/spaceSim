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

  vec3d operator+(const vec3d& vec) const {
    return vec3d(x + vec.x, y + vec.y, z + vec.z);
  }

  vec3d operator-(const vec3d& vec) const {
    return vec3d(x - vec.x, y - vec.y, z - vec.z);
  }

  vec3d operator*(const double& scale) const {
    return vec3d(x * scale, y * scale, z * scale);
  }

  vec3d operator/(const double& scale) const {
    return vec3d(x / scale, y / scale, z / scale);
  }

  double norm() const { return sqrt(x * x + y * y + z * z); }
};

double norm(const double* pos);
double clamp(const double val, const double minVal, const double maxVal);

#define log dWebotsConsolePrintf