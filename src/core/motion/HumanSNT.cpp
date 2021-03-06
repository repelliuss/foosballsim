#include <Transformation.hpp>
#include <motion/HumanSNT.hpp>

using namespace godot;

void HumanSNT::_register_methods() {
  register_method("_ready", &HumanSNT::_ready);
  register_method("_process", &HumanSNT::_physics_process);
  register_method("on_new_position", &HumanSNT::on_new_position);
}

HumanSNT::HumanSNT() noexcept {}

void HumanSNT::_init() { ArmMotion::_init(); }

void HumanSNT::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_human_snt_position_changed", this, "on_new_position");
}

void HumanSNT::on_new_position(int pos) noexcept {
  dispatcher.add(Transformation::transform_arm_z(pos));
}

void HumanSNT::_physics_process(float deltatime) {
  if (dispatcher.next_pos(transform.origin.z, deltatime)) {
    set_transform(transform);
  }
}
