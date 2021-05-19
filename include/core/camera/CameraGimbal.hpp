#ifndef CAMERAGIMBAL_HPP_
#define CAMERAGIMBAL_HPP_

#include <Godot.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <Spatial.hpp>

#define PI 3.141593
#define MAX_ZOOM 2.2
#define MIN_ZOOM 0.7
#define ZOOM_SPEED 0.09

namespace godot {
class CameraGimbal : public Spatial {
  GODOT_CLASS(CameraGimbal, Spatial)
public:
  static void _register_methods();
  CameraGimbal() noexcept;
  void _init();
  void _process(float delta);
  void get_input_keyboard(float delta);
  void _unhandled_input(InputEvent *event);

private:
  bool current;
  float cam_zoom;
  float rotation_speed;
  Input *input;
  Spatial *innerGimbal;
};
} // namespace godot

#endif // CAMERAGIMBAL_HPP_
