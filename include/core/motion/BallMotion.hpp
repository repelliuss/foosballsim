#ifndef BALL_MOTION_HPP_
#define BALL_MOTION_HPP_

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <util/FixedDispatcher2.hpp>

namespace godot {
class BallMotion : public KinematicBody {
  GODOT_CLASS(BallMotion, KinematicBody)

public:
  static void _register_methods();

  BallMotion() noexcept;

  void _init();

  void _process(float delta);

private:
  float speed;
  Transform transform;
  util::FixedDispatcher2<6> dispatcher;
};
} // namespace godot

#endif // BALL_MOTION_HPP_
