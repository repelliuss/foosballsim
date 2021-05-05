#ifndef FIXED_DISPATCHER_HPP_
#define FIXED_DISPATCHER_HPP_

#include <array>
#include <cmath>

using namespace std;

namespace godot {

template <size_t Size> class FixedDispatcher {

public:
  constexpr FixedDispatcher(const array<float, Size> &data, const float &speed,
                            const float epsilon)
      : data{data}, speed{speed}, epsilon{epsilon}, index{0} {}

  bool next_pos(float &next, float deltatime) {
    if (index >= Size) {
      return false;
    }

    float deltapos = data[index] - next;

    next += deltapos * deltatime * speed;

    if (fabs(deltapos) < epsilon) {
      ++index;
    }

    return true;
  }

private:
  const array<float, Size> data;
  int index;
  const float &speed;
  const float epsilon;
};
} // namespace godot

#endif // FIXED_DISPATCHER_HPP_
