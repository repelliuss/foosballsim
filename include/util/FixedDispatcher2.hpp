#ifndef FIXED_DISPATCHER_2_HPP_
#define FIXED_DISPATCHER_2_HPP_

#include <array>
#include <cmath>

using namespace std;

namespace util {

template <size_t Size> class FixedDispatcher2 {

public:
  constexpr FixedDispatcher2(const array<array<float, 2>, Size> &data,
                             const float &speed, const float epsilon) noexcept
      : data{data}, speed{speed}, epsilon{epsilon}, index{0} {}

  bool next_pos(float &next1, float &next2, float deltatime) noexcept {
    if (index >= Size) {
      return false;
    }

    float deltapos1 = data[index][0] - next1;
    float deltapos2 = data[index][1] - next2;

    next1 += deltapos1 * deltatime * speed;
    next2 += deltapos2 * deltatime * speed;

    if (fabs(deltapos1) < epsilon && fabs(deltapos2) < epsilon) {
      ++index;
    }

    return true;
  }

private:
  const array<array<float, 2>, Size> data;
  int index;
  const float &speed;
  const float epsilon;
};
} // namespace util

#endif // FIXED_DISPATCHER_2_HPP_
