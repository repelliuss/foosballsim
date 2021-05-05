#include <motion/R4Motion.hpp>

using namespace godot;

void R4Motion::_register_methods() {
  register_method("_process", &R4Motion::_process);
  register_property<R4Motion, float>("speed", &R4Motion::speed, 1.5);
}

R4Motion::R4Motion() noexcept
    : ArmMotion({1, 2, 3, 4}, speed, 0.1) {}

void R4Motion::_init() noexcept {
  ArmMotion::_init();
  speed = 1.5;
}

void R4Motion::_process(float delta) { ArmMotion::_process(delta); }
