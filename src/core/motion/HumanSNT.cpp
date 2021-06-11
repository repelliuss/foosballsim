#include <Constants.hpp>
#include <Transformation.hpp>
#include <motion/HumanSNT.hpp>

using namespace godot;

void HumanSNT::_register_methods() {
  register_method("_ready", &HumanSNT::_ready);
  register_method("_process", &HumanSNT::_process);
  register_method("on_new_position", &HumanSNT::on_new_position);
}

HumanSNT::HumanSNT() noexcept : ravg{constants::default_run_avg_cap} {}

void HumanSNT::_init() { ArmMotion::_init(); }

void HumanSNT::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_human_snt_position_changed", this, "on_new_position");
  ravg.add(transform.origin.z);
}

void HumanSNT::on_new_position(int pos) noexcept {
  ravg.add(Transformation::transform_z(pos));
}

void HumanSNT::_process(float deltatime) {
  if (ravg.next_pos(transform.origin.z, deltatime)) {
    set_transform(transform);
  }
}
