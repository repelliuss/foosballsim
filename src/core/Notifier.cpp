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
  register_signal<Notifier>((char *)"on_human_snt_position_changed",
                            "human_snt_position", GODOT_VARIANT_TYPE_INT);
  register_signal<Notifier>((char *)"on_human_gk_position_changed",
                            "human_gk_position", GODOT_VARIANT_TYPE_INT);
}

Notifier::Notifier() : listener{"234.5.5.5", 10200} {}

void Notifier::_init() {}

void Notifier::_process(float delta) {
  if (listener.next(data.raw) == 0) {
    int ball_position_x = data.get_ball_position_x();
    int ball_position_z = data.get_ball_position_z();
    int arm_snt_position = data.get_arm_snt_position();
    int arm_gk_position = data.get_arm_gk_position();
    int human_snt_position = data.get_human_snt_position();
    int human_gk_position = data.get_human_gk_position();

    if (ball_position_x >= 0 && ball_position_x <= org_x_length &&
        ball_position_z >= org_z_offset && ball_position_z <= org_z_length) {
      emit_signal("on_ball_position_changed", ball_position_x, ball_position_z);
    }

    if (arm_snt_position >= org_z_offset && arm_snt_position <= org_z_length) {
      emit_signal("on_arm_snt_position_changed", arm_snt_position);
    }

    if (arm_gk_position >= org_z_offset && arm_gk_position <= org_z_length) {
      emit_signal("on_arm_gk_position_changed", arm_gk_position);
    }

    if (human_gk_position >= org_z_offset &&
        human_gk_position <= org_z_length) {
      emit_signal("on_human_gk_position_changed", human_gk_position);
    }

    if (human_snt_position >= org_z_offset &&
        human_snt_position <= org_z_length) {
      emit_signal("on_human_snt_position_changed", human_snt_position);
    }
  }
}

int Notifier::Data::get_ball_position_x() const noexcept { return raw[0]; }

int Notifier::Data::get_ball_position_z() const noexcept { return raw[1]; }

int Notifier::Data::get_arm_snt_position() const noexcept { return raw[2]; }

int Notifier::Data::get_arm_gk_position() const noexcept { return raw[3]; }

int Notifier::Data::get_human_gk_position() const noexcept { return raw[4]; }

int Notifier::Data::get_human_snt_position() const noexcept { return raw[5]; }

int Notifier::Data::get_score_human() const noexcept { return raw[6]; }

int Notifier::Data::get_score_robot() const noexcept { return raw[7]; }
