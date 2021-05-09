#include <Notifier.hpp>

using namespace godot;

void Notifier::_register_methods() {
  register_method("_process", &Notifier::_process);

  register_signal<Notifier>((char *)"on_ball_position_changed", "ball_position_x",
                            GODOT_VARIANT_TYPE_INT, "ball_position_z",
                            GODOT_VARIANT_TYPE_INT);
  register_signal<Notifier>((char *)"on_arm_snt_position_changed",
                            "arm_snt_position", GODOT_VARIANT_TYPE_INT);
  register_signal<Notifier>((char *)"on_arm_gk_position_changed",
                            "arm_gk_position", GODOT_VARIANT_TYPE_INT);
}

Notifier::Notifier() : listener{"234.5.5.5", 10200} {}

void Notifier::_init() {}

void Notifier::_process(float delta) {
  if (listener.next(data.raw) == 0) {
    emit_signal("on_ball_position_changed", data.get_ball_position_x(),
                data.get_ball_position_z());
    emit_signal("on_arm_snt_position_changed", data.get_arm_snt_position());
    emit_signal("on_arm_gk_position_changed", data.get_arm_gk_position());
  }
}
