#include <motion/R3Motion.hpp>

using namespace godot;

void R3Motion::_register_methods() {
  register_method("_process", &R3Motion::_process);
  register_property<R3Motion, float>("speed", &R3Motion::speed, 3.0);
}

R3Motion::R3Motion() noexcept
    : ArmMotion({-1, 3.118, -3.67, 2.984, -1, 2.425}, speed, 0.05) {}

void R3Motion::_init() noexcept {
  ArmMotion::_init();
  speed = 3.0;
}

void R3Motion::_process(float delta) { ArmMotion::_process(delta); }
