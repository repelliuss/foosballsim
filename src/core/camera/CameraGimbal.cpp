#include <Defs.hpp>
#include <Math.hpp>
#include <Vector3.hpp>
#include <camera/CameraGimbal.hpp>
using namespace godot;

void CameraGimbal::_register_methods() {
  register_method("_process", &CameraGimbal::_process);
  register_method("get_input_keyboard", &CameraGimbal::get_input_keyboard);
  register_property<CameraGimbal, float>("rotation_speed",
                                         &CameraGimbal::rotation_speed, PI / 2);
}

CameraGimbal::CameraGimbal() noexcept {}

void CameraGimbal::_process(float delta) {
  get_input_keyboard(delta);
  Vector3 v = innerGimbal->get_rotation();
  if (v.z < -1) {
    v.z = -1;
  }
  if (v.z > 0.5) {
    v.z = 0.5;
  }
  innerGimbal->set_rotation(v);
}

void CameraGimbal::_init() {
  input = Input::get_singleton();
  rotation_speed = PI / 2;
}

void CameraGimbal::get_input_keyboard(float delta) {
  int y_rot = 0;
  int x_rot = 0;
  auto v3 = Vector3();

  if (input->is_action_pressed("cam_right")) {
    y_rot += 1;
  }
  if (input->is_action_pressed("cam_left")) {
    y_rot -= 1;
  }

  rotate_object_local(v3.UP, y_rot * rotation_speed * delta);

  if (input->is_action_pressed("cam_up")) {
    x_rot -= 1;
  }
  if (input->is_action_pressed("cam_down")) {
    x_rot += 1;
  }
  Node *node = get_node("InnerGimbal");
  innerGimbal = Object::cast_to<Spatial>(node);
  innerGimbal->rotate_object_local(v3.FORWARD, x_rot * rotation_speed * delta);
}
