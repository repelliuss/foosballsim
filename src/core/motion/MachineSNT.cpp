#include <motion/MachineSNT.hpp>
#include <Transformation.hpp>

using namespace godot;

void MachineSNT::_register_methods() {
  register_method("_ready", &MachineSNT::_ready);
  register_method("update_position", &MachineSNT::update_position);
}

MachineSNT::MachineSNT() noexcept {}

void MachineSNT::_init() {
  ArmMotion::_init();
  transform = get_transform();
}

void MachineSNT::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_arm_snt_position_changed", this, "update_position");
}

void MachineSNT::update_position(int pos) noexcept {
  transform.origin.z = Transformation::transform_z(pos);
  set_transform(transform);
}
