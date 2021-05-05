#include <motion/BallMotion.hpp>

using namespace godot;

void BallMotion::_register_methods() {
  register_method("_process", &BallMotion::_process);
  register_property<BallMotion, float>("speed", &BallMotion::speed, 3.0);
}

BallMotion::BallMotion() noexcept
    : dispatcher{{{{{3.4, 4}},
                  {{-4.985, -16.543}},
                  {{13.54, 0}},
                  {{-13.496, 10.402}},
                  {{-6.861, 16.122}},
                  {{-0.699, -27.976}}}},
                 speed, 0.2f} {}

void BallMotion::_init() {
  speed = 3.0;
  transform = get_transform();
}

void BallMotion::_process(float delta) {
  if (dispatcher.next_pos(transform.origin.x, transform.origin.z, delta)) {
    set_transform(transform);
  }
}
