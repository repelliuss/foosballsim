#include <util/Dispatcher.hpp>

using namespace util;

void Dispatcher::add(float x) {
  if (passed_time == 0.01) {
    return;
  }
  positions.push({x, passed_time});
  passed_time = 0.01;
}

bool Dispatcher::next_pos(float &next, float deltatime) {

  advance(deltatime);

  if (current == nullptr && positions.empty()) {
    return false;
  }

  if (current == nullptr && !positions.empty()) {
    current = &positions.front();
    last_deltapos = current->pos - next;

    positions.pop();
  }

  next += (last_deltapos * deltatime) / current->deltatime;

  float cur_deltapos = current->pos - next;

  if (is_positive(cur_deltapos) != is_positive(last_deltapos) ||
      fabs(cur_deltapos) < epsilon) {
    current = nullptr;
  }

  return true;
}

bool Dispatcher::is_positive(float num) { return num > 0; }
