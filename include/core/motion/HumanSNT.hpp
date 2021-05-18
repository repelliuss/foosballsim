#ifndef HUMAN_SNT_HPP_
#define HUMAN_SNT_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class HumanSNT : public ArmMotion {
  GODOT_CLASS(HumanSNT, ArmMotion)

public:
  static void _register_methods();

  HumanSNT() noexcept;

  void _init();
};
} // namespace godot

#endif // HUMAN_SNT_HPP_
