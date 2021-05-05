#include <motion/B3Motion.hpp>
#include <motion/B4Motion.hpp>
#include <motion/BallMotion.hpp>
#include <motion/R3Motion.hpp>
#include <motion/R4Motion.hpp>

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
  godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT
godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
  godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
  godot::Godot::nativescript_init(handle);

  godot::register_class<godot::BallMotion>();
  godot::register_class<godot::B3Motion>();
  godot::register_class<godot::R3Motion>();
  godot::register_class<godot::R4Motion>();
  godot::register_class<godot::B4Motion>();
}
