#include <motion/BallMotion.hpp>

using namespace godot;

void BallMotion::_register_methods() {
  register_method("_process", &BallMotion::_process);
  register_property<BallMotion, float>("speed", &BallMotion::speed, 3.0);
}

BallMotion::BallMotion()
    : x_dispatcher{{3.4, -4.985, 13.54, -13.496, -6.861, -0.699}, speed, 0.2},
      z_dispatcher{{4, -16.543, 0, 10.402, 16.122, -27.976}, speed, 0.2} {}

void BallMotion::_init() {
  speed = 3.0;
  transform = get_transform();
}

void BallMotion::_process(float delta) {

  if (x_dispatcher.next_pos(transform.origin.x, delta) &&
      z_dispatcher.next_pos(transform.origin.z, delta)) {
    set_transform(transform);
  }
}
