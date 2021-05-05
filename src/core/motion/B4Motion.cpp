#include <motion/B4Motion.hpp>

using namespace godot;

void B4Motion::_register_methods() {
  register_method("_process", &B4Motion::_process);
  register_property<B4Motion, float>("speed", &B4Motion::speed, 2.5);
}

B4Motion::B4Motion() noexcept
    : ArmMotion({1, -2, 1.049}, speed, 0.05) {}

void B4Motion::_init() noexcept {
  ArmMotion::_init();
  speed = 2.5;
}

void B4Motion::_process(float delta) { ArmMotion::_process(delta); }
