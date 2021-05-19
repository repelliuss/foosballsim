#ifndef DISPATCHER_2_CPP
#define DISPATCHER_2_CPP

#include <Vector2.hpp>
#include <cmath>
#include <queue>

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
  float passed_time = 0.001;
  bool done_x, done_y;
  godot::Vector2 last_deltapos;
  PositionInfo *current = nullptr;
  static constexpr float epsilon = 0.005;

  void advance(float time) { passed_time += time; }
  bool is_positive(float num);
};
} // namespace util

#endif // DISPATCHER_2_CPP
