#ifndef DISPATCHER_CPP
#define DISPATCHER_CPP

#include <cmath>
#include <queue>

using namespace std;

namespace util {

class Dispatcher {
public:
  void add(float x);
  bool next_pos(float &next, float deltatime);

private:
  struct PositionInfo {
    float pos;
    float deltatime;

    inline PositionInfo(float p, float t) : pos{p}, deltatime{t} {}
  };

  queue<PositionInfo> positions;
  float passed_time = 0.01;
  float last_deltapos;
  PositionInfo *current = nullptr;
  static constexpr float epsilon = 0.5;

  void advance(float time) { passed_time += time; }
};
} // namespace util

#endif // DISPATCHER_CPP
