#ifndef MACHINE_GK_HPP_
#define MACHINE_GK_HPP_

#include <motion/ArmMotion.hpp>

namespace godot {
class MachineGK : public ArmMotion {
  GODOT_CLASS(MachineGK, ArmMotion)

public:
  static void _register_methods();

  MachineGK() noexcept;

  void _init();
  void _ready();

  void update_position(int pos) noexcept;

private:
  Transform transform;
};
} // namespace godot

#endif // MACHINE_GK_HPP_
