#ifndef BALL_MOTION_HPP_
#define BALL_MOTION_HPP_

#include <Godot.hpp>
#include <KinematicBody.hpp>

namespace godot {
class BallMotion : public KinematicBody {
  GODOT_CLASS(BallMotion, KinematicBody)

public:
  static void _register_methods();

  BallMotion() noexcept;

  void _init();
  void _ready();

  void update_position(int x, int z);

private:
  Transform transform;
};
} // namespace godot

#endif // BALL_MOTION_HPP_
