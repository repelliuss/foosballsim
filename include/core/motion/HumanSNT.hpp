#ifndef HUMAN_SNT_HPP_
#define HUMAN_SNT_HPP_

#include <motion/ArmMotion.hpp>
#include <util/RunningAverage.hpp>

namespace godot {
class HumanSNT : public ArmMotion {
  GODOT_CLASS(HumanSNT, ArmMotion)

public:
  static void _register_methods();

  HumanSNT() noexcept;

  void _init();
  void _ready();
  void _process(float deltatime);

  void on_new_position(int pos) noexcept;

private:
  util::RunningAverage ravg;
};
} // namespace godot

#endif // HUMAN_SNT_HPP_
