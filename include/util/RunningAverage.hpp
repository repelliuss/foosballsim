#ifndef RUNNING_AVERAGE_H_
#define RUNNING_AVERAGE_H_

#include <queue>

using namespace std;

namespace util {
class RunningAverage {
public:
  RunningAverage(int cap);
  void add(float x);
  bool next_pos(float &next, float deltatime);

private:
  queue<float> data;
  float sum = 0.0;
  int cap;
};
} // namespace util


#endif // RUNNING_AVERAGE_H_
