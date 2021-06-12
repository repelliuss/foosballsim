#include <Constants.hpp>
#include <cstdio>
#include <util/Dispatcher2.hpp>

using namespace util;

void Dispatcher2::add(float x, float z) {
  if (skipped_data > data_interval) {
    skipped_data = 0;
    if (passed_time == 0.01) {
      return;
    }
    if (x > constants::dimensions::sim_x_length) {
      x = constants::dimensions::sim_x_length;
    } else if (x < 0) {
      x = 0;
    }
    if (z > constants::dimensions::sim_z_length) {
      z = constants::dimensions::sim_z_length;
    } else if (z < 0) {
      z = 0;
    }
    passed_time -= passed_time / 3;
    positions.push({{x, z}, passed_time});
    passed_time = 0.01;
  } else {
    ++skipped_data;
  }
}

bool Dispatcher2::next_pos(float &next1, float &next2, float deltatime) {

  advance(deltatime);
  timeout += deltatime;

  if (current == nullptr && positions.empty()) {
    return false;
  }

  if (current == nullptr && !positions.empty()) {
    current = &positions.front();
    last_deltapos.x = current->pos.x - next1;
    last_deltapos.y = current->pos.y - next2;

    done_x = done_y = false;

    timeout = 0.0;

    positions.pop();
  }

  if (current->deltatime == 0.0 || timeout >= current->deltatime) {
    current = nullptr;
    return false;
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
