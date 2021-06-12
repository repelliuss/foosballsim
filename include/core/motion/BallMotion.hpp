#ifndef BALL_MOTION_HPP_
#define BALL_MOTION_HPP_

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <util/Dispatcher2.hpp>

namespace godot {
class BallMotion : public KinematicBody {
  GODOT_CLASS(BallMotion, KinematicBody)

public:
  static void _register_methods();

  BallMotion() noexcept;

  void _init();
  void _ready();
  void _physics_process(float deltatime);

  void on_new_position(int x, int z);

private:
  Transform transform;
  util::Dispatcher2 dispatcher;
};
} // namespace godot

#endif // BALL_MOTION_HPP_
