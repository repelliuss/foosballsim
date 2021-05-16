#ifndef CAMERAGIMBAL_HPP_
#define CAMERAGIMBAL_HPP_

#include <Godot.hpp>
#include <Input.hpp>
#include <Spatial.hpp>

#define PI 3.141593

namespace godot {
class CameraGimbal : public Spatial {
  GODOT_CLASS(CameraGimbal, Spatial)
public:
  static void _register_methods();
  CameraGimbal() noexcept;
  void _init();
  void _process(float delta);
  void get_input_keyboard(float delta);

private:
  float rotation_speed;
  Input *input;
  Node *childNode;
};
} // namespace godot

#endif // CAMERAGIMBAL_HPP_
