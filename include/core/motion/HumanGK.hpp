#ifndef HUMAN_GK_HPP_
#define HUMAN_GK_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class HumanGK : public ArmMotion {
  GODOT_CLASS(HumanGK, ArmMotion)

public:
  static void _register_methods();

  HumanGK() noexcept;

  void _init();
};
} // namespace godot

#endif // HUMAN_GK_HPP_
