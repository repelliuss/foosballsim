#include <Transformation.hpp>

// simulation
// ==========
// 2.321 Z axis length
// 3.644 X axis length

// original
// =========
// 390 Z axis length
// 615 X axis length

// simulation rate: 1.5700129254631623
// original rate: 1.5769230769230769
// error % percent:  0.44388078630310057

// Machine GK - X pos
// original: 55
// simulation: 0.326

// Human GK - X pos
// original: 560
// simulation: 3.318

// Machine SNT - X pos
// original: 375
// simulation: 2.222

// Human SNT - X pos
// original: 240
// simulation: 1.422

using namespace transform;
using namespace constant;

constexpr float detail::transform_point(float when_length, float then_point,
                                        float if_length) {
  return (if_length * then_point) / when_length;
}

constexpr float transform_x(float org_x) {
  return detail::transform_point(org_x_length, org_x, sim_x_length);
}

constexpr float transform_z(float org_z) {
  return detail::transform_point(org_z_length - org_z_offset, org_z,
                                 sim_z_length);
}
