#include <cstdio>
#include <util/Dispatcher2.hpp>

using namespace util;

void Dispatcher2::add(float x, float y) {
  if (passed_time == 0.001) {
    return;
  }
  positions.push({{x, y}, passed_time});
  passed_time = 0.001;
}

bool Dispatcher2::next_pos(float &next1, float &next2, float deltatime) {

  advance(deltatime);

  if (current == nullptr && positions.empty()) {
    return false;
  }

  if (current == nullptr && !positions.empty()) {
    current = &positions.front();
    last_deltapos.x = current->pos.x - next1;
    last_deltapos.y = current->pos.y - next2;

    done_x = done_y = false;

    positions.pop();
  }

  if (!done_x)
    next1 += (last_deltapos.x * deltatime) / current->deltatime;

  if (!done_y)
    next2 += (last_deltapos.y * deltatime) / current->deltatime;

  godot::Vector2 cur_deltapos{current->pos.x - next1, current->pos.y - next2};

  if (is_positive(cur_deltapos.x) != is_positive(last_deltapos.x) ||
      fabs(cur_deltapos.x) < epsilon) {
    done_x = true;
  }

  if (is_positive(cur_deltapos.y) != is_positive(last_deltapos.y) ||
      fabs(cur_deltapos.y) < epsilon) {
    done_y = true;
  }

  if (done_x && done_y) {
    current = nullptr;
  }

  return true;
}

bool Dispatcher2::is_positive(float num) { return num > 0; }
