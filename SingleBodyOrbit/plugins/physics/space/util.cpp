#include "util.hpp"

double clamp(const double val, const double minVal, const double maxVal) {
  if (val < minVal)
    return minVal;
  if (val > maxVal)
    return maxVal;

  return val;
}

vec3d vec3d::operator+(const vec3d& vec) const {
  return vec3d(x + vec.x, y + vec.y, z + vec.z);
}

vec3d vec3d::operator-(const vec3d& vec) const {
  return vec3d(x - vec.x, y - vec.y, z - vec.z);
}

vec3d vec3d::operator*(const double& scale) const {
  return vec3d(x * scale, y * scale, z * scale);
}

vec3d vec3d::operator/(const double& scale) const {
  return vec3d(x / scale, y / scale, z / scale);
}

double vec3d::norm() const {
  return sqrt(x * x + y * y + z * z);
}

vec3d vec3d::unit() const {
  return *this / norm();
}