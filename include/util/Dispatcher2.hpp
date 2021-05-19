#ifndef DISPATCHER_2_CPP
#define DISPATCHER_2_CPP

#include <Vector2.hpp>
#include <queue>
#include <cmath>

using namespace std;

namespace util {

class Dispatcher2 {
public:
  void add(float x, float y);

  bool next_pos(float &next1, float &next2, float deltatime);

private:
  struct PositionInfo {
    godot::Vector2 pos;
    float deltatime;

    inline PositionInfo(godot::Vector2 p, float t) : pos{p}, deltatime{t} {}
  };

  queue<PositionInfo> positions;
  float passed_time = 0.01;
  godot::Vector2 last_deltapos;
  PositionInfo *current = nullptr;
  static constexpr float epsilon = 0.5;

  void advance(float time) { passed_time += time; }
};
} // namespace util

#endif // DISPATCHER_2_CPP
