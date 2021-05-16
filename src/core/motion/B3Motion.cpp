#include <motion/B3Motion.hpp>

using namespace godot;

void B3Motion::_register_methods() {
  register_method("_ready", &B3Motion::_ready);
  register_method("update_position", &B3Motion::update_position);
}

B3Motion::B3Motion() noexcept {}

void B3Motion::_init() { ArmMotion::_init(); }

void B3Motion::_ready() {
  get_node(NodePath("../../Table"))
      ->connect("on_arm_gk_position_changed", this, "update_position");
}

void B3Motion::update_position(int pos) noexcept {
  printf("GK position updated: %d\n", pos);
}
