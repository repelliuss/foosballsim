#ifndef ARM_MOTION_HPP_
#define ARM_MOTION_HPP_

#include <Godot.hpp>
#include <KinematicBody.hpp>

namespace godot {
class ArmMotion : public KinematicBody {

public:
  ArmMotion() noexcept;

  void _init();

private:
  Transform transform;
};
} // namespace godot

#endif // ARM_MOTION_HPP_
