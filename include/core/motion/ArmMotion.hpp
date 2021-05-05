#ifndef ARM_MOTION_HPP_
#define ARM_MOTION_HPP_

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <util/FixedDispatcher.hpp>

namespace godot {
template <size_t Size> class ArmMotion : public KinematicBody {

public:
  ArmMotion(const array<float, Size> &data, const float &speed,
            const float epsilon) noexcept
      : dispatcher{data, speed, epsilon} {}

  void _init() noexcept { transform = get_transform(); }

  void _process(float delta) noexcept {
    if (dispatcher.next_pos(transform.origin.x, delta)) {
      set_transform(transform);
    }
  }

private:
  Transform transform;
  util::FixedDispatcher<Size> dispatcher;
};
} // namespace godot

#endif // ARM_MOTION_HPP_
