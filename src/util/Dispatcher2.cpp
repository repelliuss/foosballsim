#include <util/Dispatcher2.hpp>

using namespace util;

void Dispatcher2::add(float x, float y) {
  positions.push({{x, y}, passed_time});
  passed_time = 0;
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

    positions.pop();
  }

  next1 += (last_deltapos.x * deltatime) / current->deltatime;
  next2 += (last_deltapos.y * deltatime) / current->deltatime;

  godot::Vector2 cur_deltapos{current->pos.x - next1, current->pos.y - next2};

  if (fabs(cur_deltapos.x) < epsilon && fabs(cur_deltapos.y) < epsilon) {
    current = nullptr;
  }

  return true;
}
