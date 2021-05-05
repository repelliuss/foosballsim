#ifndef B4_MOTION_HPP_
#define B4_MOTION_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class B4Motion : public ArmMotion<3> {
  GODOT_CLASS(B4Motion, ArmMotion)

private:
  float speed;

public:
  static void _register_methods();

  B4Motion() noexcept;

  void _init() noexcept;
  void _process(float delta);
};
} // namespace godot

#endif // B4_MOTION_HPP_
