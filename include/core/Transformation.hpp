#ifndef TRANSFORMATION_HPP_
#define TRANSFORMATION_HPP_

namespace transform {
namespace constant {
inline constexpr float org_x_length = 615;

inline constexpr float org_z_length = 435;
inline constexpr float org_z_offset = 45;

inline constexpr float sim_x_length = 3.644;
inline constexpr float sim_z_length = 2.321;
} // namespace constant

namespace detail {
constexpr float transform_point(float when_length, float then_point,
                                float if_length);
}

constexpr float transform_z(float org_z);
constexpr float transform_x(float org_x);
} // namespace transform

#endif // TRANSFORMATION_HPP_
