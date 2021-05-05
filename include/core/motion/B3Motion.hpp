#ifndef B3_MOTION_HPP_
#define B3_MOTION_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class B3Motion : public ArmMotion<3> {
  GODOT_CLASS(B3Motion, ArmMotion)

private:
  float speed;

public:
  static void _register_methods();

  B3Motion() noexcept;

  void _init() noexcept;
  void _process(float delta);
};
} // namespace godot

#endif // B3_MOTION_HPP_
