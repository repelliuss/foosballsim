#ifndef B4_MOTION_HPP_
#define B4_MOTION_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class B4Motion : public ArmMotion {
  GODOT_CLASS(B4Motion, ArmMotion)

public:
  static void _register_methods();

  B4Motion() noexcept;

  void _init();
  void _ready();

  void update_position(int pos) noexcept;
};
} // namespace godot

#endif // B4_MOTION_HPP_
