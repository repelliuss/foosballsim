#ifndef MACHINE_GK_HPP_
#define MACHINE_GK_HPP_

#include <motion/ArmMotion.hpp>
#include <util/Dispatcher.hpp>

namespace godot {
class MachineGK : public ArmMotion {
  GODOT_CLASS(MachineGK, ArmMotion)

public:
  static void _register_methods();

  MachineGK() noexcept;

  void _init();
  void _ready();
  void _process(float deltatime);

  void on_new_position(int pos) noexcept;

private:
  util::Dispatcher dispatcher;
};
} // namespace godot

#endif // MACHINE_GK_HPP_
