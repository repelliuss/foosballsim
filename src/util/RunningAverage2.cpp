#include <util/RunningAverage2.hpp>

using namespace util;

RunningAverage2::RunningAverage2(int cap) : cap{cap} {}

void RunningAverage2::add(float x, float y) {
  sum_x += x;
  sum_y += y;
  data_x.push(x);
  data_y.push(y);

  if (data_x.size() > cap) {
    sum_x -= data_x.front();
    sum_y -= data_y.front();
    data_x.pop();
    data_y.pop();
  }
}

bool RunningAverage2::next_pos(float &next1, float &next2, float deltatime) {

    next1 = sum_x / cap;
    next2 = sum_y / cap;

    return true;
}
