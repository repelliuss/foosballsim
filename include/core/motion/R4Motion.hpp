#ifndef R4_MOTION_HPP_
#define R4_MOTION_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class R4Motion : public ArmMotion {
  GODOT_CLASS(R4Motion, ArmMotion)

public:
  static void _register_methods();

  R4Motion() noexcept;

  void _init();
};
} // namespace godot

#endif // R4_MOTION_HPP_
