#ifndef RUNNING_AVERAGE2_H_
#define RUNNING_AVERAGE2_H_

#include <queue>

using namespace std;

namespace util {
class RunningAverage2 {
public:
  RunningAverage2(int cap);
  void add(float x, float y);
  bool next_pos(float &next1, float &next2, float deltatime);

private:
  queue<float> data_x;
  queue<float> data_y;
  float sum_x = 0.0;
  float sum_y = 0.0;
  int cap;
};
} // namespace util

#endif // RUNNING_AVERAGE2_H_
