#include <motion/BallMotion.hpp>

using namespace godot;

void BallMotion::_register_methods() {
  register_method("_ready", &BallMotion::_ready);
  register_method("update_position", &BallMotion::update_position);
}

BallMotion::BallMotion() noexcept {}

void BallMotion::_init() { transform = get_transform(); }

void BallMotion::_ready() {
  get_node(NodePath("../../Table"))
      ->connect("on_ball_position_changed", this, "update_position");
}

void BallMotion::update_position(int x, int z) {
  printf("Ball position updated %d %d\n", x, z);
}
