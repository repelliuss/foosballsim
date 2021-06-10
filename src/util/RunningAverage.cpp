#include <util/RunningAverage.hpp>

using namespace util;

RunningAverage::RunningAverage(int cap) : cap{cap} {}

void RunningAverage::add(float x) {
  sum += x;
  data.push(x);

  if (data.size() > cap) {
    sum -= data.front();
    data.pop();
  }
}

bool RunningAverage::next_pos(float &next, float deltatime) {

    next = sum / cap;

    return true;
}
