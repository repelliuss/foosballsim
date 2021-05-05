#ifndef BALL_MOTION_HPP_
#define BALL_MOTION_HPP_

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <util/FixedDispatcher.hpp>

namespace godot {
class BallMotion : public KinematicBody {
  GODOT_CLASS(BallMotion, KinematicBody)

private:
  float speed;
  Transform transform;
  FixedDispatcher<6> x_dispatcher;
  FixedDispatcher<6> z_dispatcher;

public:
  static void _register_methods();

  BallMotion();

  void _init();

  void _process(float delta);
};
} // namespace godot

#endif // BALL_MOTION_HPP_
