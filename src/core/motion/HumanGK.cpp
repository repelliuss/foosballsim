#include <Constants.hpp>
#include <Transformation.hpp>
#include <motion/HumanGK.hpp>

using namespace godot;

void HumanGK::_register_methods() {
  register_method("_ready", &HumanGK::_ready);
  register_method("_process", &HumanGK::_process);
  register_method("on_new_position", &HumanGK::on_new_position);
}

HumanGK::HumanGK() noexcept : ravg{constants::default_run_avg_cap} {}

void HumanGK::_init() { ArmMotion::_init(); }

void HumanGK::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_human_gk_position_changed", this, "on_new_position");
  ravg.add(transform.origin.z);
}

void HumanGK::on_new_position(int pos) noexcept {
  ravg.add(Transformation::transform_z(pos));
}

void HumanGK::_process(float deltatime) {
  if (ravg.next_pos(transform.origin.z, deltatime)) {
    set_transform(transform);
  }
}
