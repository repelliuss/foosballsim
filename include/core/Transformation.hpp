#ifndef TRANSFORMATION_HPP_
#define TRANSFORMATION_HPP_

class Transformation {
public:

  static float transform_z(float org_z);
  static float transform_x(float org_x);

private:
  inline static constexpr float org_x_length = 615;

  inline static constexpr float org_z_length = 435;
  inline static constexpr float org_z_offset = 45;

  inline static constexpr float sim_x_length = 3.7;
  inline static constexpr float sim_z_length = 2.349;

  static float transform_point(float when_length, float then_point, float if_length);
};

#endif // TRANSFORMATION_HPP_
