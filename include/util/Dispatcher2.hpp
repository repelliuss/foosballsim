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

    PositionInfo(godot::Vector2 p, float t) : pos{p}, deltatime{t} {}
  };

  queue<PositionInfo> positions;
  float passed_time = 0.01;
  float timeout = 0.0;
  bool done_x, done_y;
  godot::Vector2 last_deltapos;
  PositionInfo *current = nullptr;
  int skipped_data = 0;
  static constexpr float epsilon = 0.05;
  static constexpr int data_interval = 0;

  /* FIXME: reset when passed_time is too big */
  void advance(float time) {
    passed_time += time;
    if(passed_time >= 2) {
      passed_time = 0.05;
    }
  }
  bool is_positive(float num);
};
} // namespace util

#endif // DISPATCHER_2_CPP
