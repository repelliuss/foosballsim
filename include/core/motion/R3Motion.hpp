#ifndef R3_MOTION_HPP_
#define R3_MOTION_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class R3Motion : public ArmMotion<6> {
  GODOT_CLASS(R3Motion, ArmMotion)

private:
  float speed{3.0f};

public:
  static void _register_methods();

  R3Motion() noexcept;

  void _init() noexcept;
  void _process(float delta);
};
} // namespace godot

#endif // R3_MOTION_HPP_
