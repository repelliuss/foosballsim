#include <motion/B4Motion.hpp>

using namespace godot;

void B4Motion::_register_methods() {
  register_method("_ready", &B4Motion::_ready);
  register_method("update_position", &B4Motion::update_position);
}

B4Motion::B4Motion() noexcept {}

void B4Motion::_init() { ArmMotion::_init(); }

void B4Motion::_ready() {
  get_node(NodePath("../../Table"))
      ->connect("on_arm_snt_position_changed", this, "update_position");
}

void B4Motion::update_position(int pos) noexcept {
  printf("SNT position updated: %d\n", pos);
}
