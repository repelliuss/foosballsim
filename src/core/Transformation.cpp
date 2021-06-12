#include <Constants.hpp>
#include <Transformation.hpp>

// simulation
// ==========
// 2.349 Z axis length
// 3.7 X axis length

// original
// =========
// 435 Z axis length
// 45 Z axis offset
// 615 X axis length

// original rate: 1.5769230769230769
// simulation rate: 1.575138356747552
// error % percent:  0.11319512747294241

// Machine GK - X pos
// original: 55
// simulation: 0.3308943089430894

// Human GK - X pos
// original: 560
// simulation: 3.3691056910569106

// Machine SNT - X pos
// original: 375
// simulation: 2.2560975609756095

// Human SNT - X pos
// original: 240
// simulation: 1.4439024390243902

using namespace constants::dimensions;

constexpr float Transformation::transform_point(float when_length,
                                                float then_point,
                                                float if_length) {
  return (if_length * then_point) / when_length;
}

float Transformation::transform_x(float org_x) {
  return transform_point(org_x_length, org_x, sim_x_length);
}

float Transformation::transform_z(float org_z) {
  return transform_point(org_z_length - org_z_offset, org_z - org_z_offset,
                         sim_z_length);
}

float Transformation::transform_arm_z(float org_z) {
  return transform_point(org_z_arm_max - org_z_arm_min, org_z - org_z_arm_min,
                         sim_arm_z_max - sim_arm_z_min) +
         sim_arm_z_min;
}
