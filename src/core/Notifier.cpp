#include <Constants.hpp>
#include <Notifier.hpp>

using namespace godot;
using namespace constants::dimensions;

void Notifier::_register_methods() {
  register_method("_process", &Notifier::_process);

  register_signal<Notifier>((char *)"on_ball_position_changed",
                            "ball_position_x", GODOT_VARIANT_TYPE_INT,
                            "ball_position_z", GODOT_VARIANT_TYPE_INT);
  register_signal<Notifier>((char *)"on_arm_snt_position_changed",
                            "arm_snt_position", GODOT_VARIANT_TYPE_INT);
  register_signal<Notifier>((char *)"on_arm_gk_position_changed",
                            "arm_gk_position", GODOT_VARIANT_TYPE_INT);
}

Notifier::Notifier() : listener{"234.5.5.5", 10200} {}

void Notifier::_init() {}

void Notifier::_process(float delta) {
  if (listener.next(data.raw) == 0) {
    int ball_position_x = data.get_ball_position_x();
    int ball_position_z = data.get_ball_position_z();
    int snt_position = data.get_arm_snt_position();
    int gk_position = data.get_arm_gk_position();

    if (ball_position_x >= 0 && ball_position_x <= org_x_length &&
        ball_position_z >= 0 && ball_position_z <= org_z_length &&
        snt_position >= 0 && snt_position <= org_z_length && gk_position >= 0 &&
        gk_position <= org_z_length) {
      emit_signal("on_ball_position_changed", ball_position_x, ball_position_z);
      emit_signal("on_arm_snt_position_changed", snt_position);
      emit_signal("on_arm_gk_position_changed", gk_position);
    }
  }
}
