#include <Constants.hpp>
#include <Transformation.hpp>
#include <motion/MachineSNT.hpp>

using namespace godot;

void MachineSNT::_register_methods() {
  register_method("_ready", &MachineSNT::_ready);
  register_method("_process", &MachineSNT::_process);
  register_method("on_new_position", &MachineSNT::on_new_position);
}

MachineSNT::MachineSNT() noexcept : ravg{constants::default_run_avg_cap} {}

void MachineSNT::_init() { ArmMotion::_init(); }

void MachineSNT::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_arm_snt_position_changed", this, "on_new_position");
  ravg.add(transform.origin.z);
}

void MachineSNT::on_new_position(int pos) noexcept {
  ravg.add(Transformation::transform_z(pos));
}

void MachineSNT::_process(float deltatime) {
  if (ravg.next_pos(transform.origin.z, deltatime)) {
    set_transform(transform);
  }
}
