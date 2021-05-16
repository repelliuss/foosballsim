#ifndef B3_MOTION_HPP_
#define B3_MOTION_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class B3Motion : public ArmMotion {
  GODOT_CLASS(B3Motion, ArmMotion)

public:
  static void _register_methods();

  B3Motion() noexcept;

  void _init();
  void _ready();

  void update_position(int pos) noexcept;
};
} // namespace godot

#endif // B3_MOTION_HPP_
