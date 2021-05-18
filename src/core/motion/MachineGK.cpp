#include <motion/MachineGK.hpp>
#include <Transformation.hpp>

using namespace godot;

void MachineGK::_register_methods() {
  register_method("_ready", &MachineGK::_ready);
  register_method("update_position", &MachineGK::update_position);
}

MachineGK::MachineGK() noexcept {}

void MachineGK::_init() {
  ArmMotion::_init();
  transform = get_transform();
}

void MachineGK::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_arm_gk_position_changed", this, "update_position");
}

void MachineGK::update_position(int pos) noexcept {
  transform.origin.z = Transformation::transform_z(pos);
  set_transform(transform);
}
