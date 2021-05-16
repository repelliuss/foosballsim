#ifndef R3_MOTION_HPP_
#define R3_MOTION_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class R3Motion : public ArmMotion {
  GODOT_CLASS(R3Motion, ArmMotion)

public:
  static void _register_methods();

  R3Motion() noexcept;

  void _init();
};
} // namespace godot

#endif // R3_MOTION_HPP_
