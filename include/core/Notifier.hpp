#ifndef NOTIFIER_HPP_
#define NOTIFIER_HPP_

#include <Godot.hpp>
#include <Object.hpp>
#include <cstdint>
#include <util/MulticastSocketListener.hpp>

using namespace std;

namespace godot {
class Notifier : public Object {
  GODOT_CLASS(Notifier, Object)
public:
  static void _register_methods();

  Notifier();

  void _init();

  void _process(float delta);

private:
  class Data {
  public:
    uint_fast16_t raw[6];

    int get_ball_position_x() const noexcept { return raw[0]; }
    int get_ball_position_z() const noexcept { return raw[1]; }
    int get_arm_snt_position() const noexcept { return raw[2]; }
    int get_arm_gk_position() const noexcept { return raw[3]; }
    int get_score_human() const noexcept { return raw[4]; }
    int get_score_robot() const noexcept { return raw[5]; }
  };

  Data data;
  util::MulticastSocketListener<decltype(data.raw)> listener;
};
} // namespace godot

#endif // NOTIFIER_HPP_
