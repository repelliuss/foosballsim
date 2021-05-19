#ifndef TRANSFORMATION_HPP_
#define TRANSFORMATION_HPP_

class Transformation {
public:

  static float transform_z(float org_z);
  static float transform_x(float org_x);

private:
  static constexpr float transform_point(float when_length, float then_point, float if_length);
};

#endif // TRANSFORMATION_HPP_
