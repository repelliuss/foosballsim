#include <Transformation.hpp>
#include <motion/HumanGK.hpp>

using namespace godot;

void HumanGK::_register_methods() {
  register_method("_ready", &HumanGK::_ready);
  register_method("_process", &HumanGK::_physics_process);
  register_method("on_new_position", &HumanGK::on_new_position);
}

HumanGK::HumanGK() noexcept {}

void HumanGK::_init() { ArmMotion::_init(); }

void HumanGK::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_human_gk_position_changed", this, "on_new_position");
}

void HumanGK::on_new_position(int pos) noexcept {
  dispatcher.add(Transformation::transform_arm_z(pos));
}

void HumanGK::_physics_process(float deltatime) {
  if (dispatcher.next_pos(transform.origin.z, deltatime)) {
    set_transform(transform);
  }
}
