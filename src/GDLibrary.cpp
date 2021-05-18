#include <motion/MachineGK.hpp>
#include <motion/MachineSNT.hpp>
#include <motion/BallMotion.hpp>
#include <motion/HumanGK.hpp>
#include <motion/HumanSNT.hpp>
#include <Notifier.hpp>

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
  godot::register_class<godot::MachineGK>();
  godot::register_class<godot::HumanGK>();
  godot::register_class<godot::HumanSNT>();
  godot::register_class<godot::MachineSNT>();
  godot::register_class<godot::Notifier>();
}
