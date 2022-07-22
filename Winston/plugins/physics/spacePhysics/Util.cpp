#include "Util.hpp"

double norm(const double *pos) {
  return sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]);
}

double clamp(const double val, const double minVal, const double maxVal) {
  if (val < minVal)
    return minVal;
  if (val > maxVal)
    return maxVal;

  return val;
}