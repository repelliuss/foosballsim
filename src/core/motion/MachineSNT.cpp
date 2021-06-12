#include <Transformation.hpp>
#include <motion/MachineSNT.hpp>

using namespace godot;

void MachineSNT::_register_methods() {
  register_method("_ready", &MachineSNT::_ready);
  register_method("_process", &MachineSNT::_physics_process);
  register_method("on_new_position", &MachineSNT::on_new_position);
}

MachineSNT::MachineSNT() noexcept {}

void MachineSNT::_init() {
  ArmMotion::_init();
  transform = get_transform();
}

void MachineSNT::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_arm_snt_position_changed", this, "on_new_position");
}

void MachineSNT::on_new_position(int pos) noexcept {
  dispatcher.add(Transformation::transform_arm_z(pos));
}

void MachineSNT::_physics_process(float deltatime) {
  if (dispatcher.next_pos(transform.origin.z, deltatime)) {
    set_transform(transform);
  }
}
