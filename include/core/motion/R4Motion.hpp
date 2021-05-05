#ifndef R4_MOTION_HPP_
#define R4_MOTION_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class R4Motion : public ArmMotion<4> {
  GODOT_CLASS(R4Motion, ArmMotion)

private:
  float speed;

public:
  static void _register_methods();

  R4Motion() noexcept;

  void _init() noexcept;
  void _process(float delta);
};
} // namespace godot

#endif // R4_MOTION_HPP_
