#include <util/Dispatcher.hpp>

using namespace util;

void Dispatcher::add(float x) {
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

  if (fabs(cur_deltapos) < epsilon) {
    current = nullptr;
  }

  return true;
}
