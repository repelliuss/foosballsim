#include <Constants.hpp>
#include <Transformation.hpp>
#include <motion/MachineGK.hpp>

using namespace godot;

void MachineGK::_register_methods() {
  register_method("_ready", &MachineGK::_ready);
  register_method("_process", &MachineGK::_process);
  register_method("on_new_position", &MachineGK::on_new_position);
}

MachineGK::MachineGK() noexcept : ravg{constants::default_run_avg_cap} {}

void MachineGK::_init() { ArmMotion::_init(); }

void MachineGK::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_arm_gk_position_changed", this, "on_new_position");
  ravg.add(transform.origin.z);
}

void MachineGK::on_new_position(int pos) noexcept {
  ravg.add(Transformation::transform_z(pos));
}

void MachineGK::_process(float deltatime) {
  if (ravg.next_pos(transform.origin.z, deltatime)) {
    set_transform(transform);
  }
}
