#include <Transformation.hpp>
#include <motion/MachineGK.hpp>

using namespace godot;

void MachineGK::_register_methods() {
  register_method("_ready", &MachineGK::_ready);
  register_method("_physics_process", &MachineGK::_physics_process);
  register_method("on_new_position", &MachineGK::on_new_position);
}

MachineGK::MachineGK() noexcept {}

void MachineGK::_init() {
  ArmMotion::_init();
  transform = get_transform();
}

void MachineGK::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_arm_gk_position_changed", this, "on_new_position");
}

void MachineGK::on_new_position(int pos) noexcept { dispatcher.add(pos); }

void MachineGK::_physics_process(float deltatime) {
  Transform transformed = transform;
  if (dispatcher.next_pos(transform.origin.z, deltatime)) {
    transformed.origin.z = Transformation::transform_z(transform.origin.z);
    set_transform(transformed);
  }
}
