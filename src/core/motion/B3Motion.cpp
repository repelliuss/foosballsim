#include <motion/B3Motion.hpp>

using namespace godot;

void B3Motion::_register_methods() {
  register_method("_process", &B3Motion::_process);
  register_property<B3Motion, float>("speed", &B3Motion::speed, 2.0);
}

B3Motion::B3Motion() noexcept
    : ArmMotion({4.131, -3.993, 2.295}, speed, 0.025) {}

void B3Motion::_init() noexcept {
  ArmMotion::_init();
  speed = 2.0;
}

void B3Motion::_process(float delta) { ArmMotion::_process(delta); }
