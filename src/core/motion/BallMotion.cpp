#include <Transformation.hpp>
#include <motion/BallMotion.hpp>

using namespace godot;

void BallMotion::_register_methods() {
  register_method("_ready", &BallMotion::_ready);
  register_method("_physics_process", &BallMotion::_physics_process);
  register_method("on_new_position", &BallMotion::on_new_position);
}

BallMotion::BallMotion() noexcept {}

void BallMotion::_init() { transform = get_transform(); }

void BallMotion::_ready() {
  get_node(NodePath("../../../Table"))
      ->connect("on_ball_position_changed", this, "on_new_position");
}

void BallMotion::on_new_position(int x, int z) {
  dispatcher.add(Transformation::transform_x(x),
                 Transformation::transform_z(z));
}

void BallMotion::_physics_process(float deltatime) {
  if (dispatcher.next_pos(transform.origin.x, transform.origin.z, deltatime)) {
    set_transform(transform);
  }
}
