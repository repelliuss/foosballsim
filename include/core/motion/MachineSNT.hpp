#ifndef MACHINE_SNT_HPP_
#define MACHINE_SNT_HPP_

#include <motion/ArmMotion.hpp>
#include <util/RunningAverage.hpp>

namespace godot {
class MachineSNT : public ArmMotion {
  GODOT_CLASS(MachineSNT, ArmMotion)

public:
  static void _register_methods();

  MachineSNT() noexcept;

  void _init();
  void _ready();
  void _process(float deltatime);

  void on_new_position(int pos) noexcept;

private:
  util::RunningAverage ravg;
};
} // namespace godot

#endif // MACHINE_SNT_HPP_
