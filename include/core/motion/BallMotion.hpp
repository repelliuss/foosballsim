#ifndef BALL_MOTION_HPP_
#define BALL_MOTION_HPP_

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <util/RunningAverage2.hpp>

namespace godot {
class BallMotion : public KinematicBody {
  GODOT_CLASS(BallMotion, KinematicBody)

public:
  static void _register_methods();

  BallMotion() noexcept;

  void _init();
  void _ready();
  void _process(float deltatime);

  void on_new_position(int x, int z);

private:
  Transform transform;
  util::RunningAverage2 ravg;
};
} // namespace godot

#endif // BALL_MOTION_HPP_
