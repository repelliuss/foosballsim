#include "Object.hpp"
#include <Camera.hpp>
#include <Defs.hpp>
#include <Vector3.hpp>
#include <camera/CameraGimbal.hpp>

using namespace godot;

void CameraGimbal::_register_methods() {
  register_method("_process", &CameraGimbal::_process);
  register_method("get_input_keyboard", &CameraGimbal::get_input_keyboard);
  register_method("_unhandled_input", &CameraGimbal::_unhandled_input);
  register_property<CameraGimbal, float>("rotation_speed",
                                         &CameraGimbal::rotation_speed, PI / 2);
  register_property<CameraGimbal, float>("cam_zoom", &CameraGimbal::cam_zoom,
                                         1);
}

CameraGimbal::CameraGimbal() noexcept { current = true; }

void CameraGimbal::_process(float delta) {
  get_input_keyboard(delta);

  Vector3 v = get_scale();
  real_t scale = v.x;
  scale += ZOOM_SPEED * (cam_zoom - scale);
  v = Vector3(scale, scale, scale);
  set_scale(v);
}

void CameraGimbal::_init() {
  input = Input::get_singleton();
  rotation_speed = PI / 2;
  cam_zoom = 1;
}

void CameraGimbal::_unhandled_input(InputEvent *event) {

  if (current) {
    if (event->is_action_pressed("cam_zoom_in")) {
      cam_zoom -= ZOOM_SPEED;
    }
    if (event->is_action_pressed("cam_zoom_out")) {
      cam_zoom += ZOOM_SPEED;
    }

    if (cam_zoom < MIN_ZOOM) {
      cam_zoom = MIN_ZOOM;
    }
    if (cam_zoom > MAX_ZOOM) {
      cam_zoom = MAX_ZOOM;
    }
  }
}

void CameraGimbal::get_input_keyboard(float delta) {
  Node *node;
  Camera *cam;
  if (current) {
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
    node = get_node("InnerGimbal");
    innerGimbal = Object::cast_to<Spatial>(node);
    innerGimbal->rotate_object_local(v3.FORWARD,
                                     x_rot * rotation_speed * delta);

    Vector3 v = innerGimbal->get_rotation();
    if (v.z < -1) {
      v.z = -1;
    }
    if (v.z > 0.5) {
      v.z = 0.5;
    }
    innerGimbal->set_rotation(v);
  }
  if (input->is_action_pressed("select_cam_1")) {
    current = true;
    node = get_node("InnerGimbal/Camera");
    cam = Object::cast_to<Camera>(node);
    cam->set_current(true);
  }
  if (input->is_action_pressed("select_cam_2")) {
    current = false;
    node = get_node("../TopCamera");
    cam = Object::cast_to<Camera>(node);
    cam->set_current(true);
  }
  if (input->is_action_pressed("select_cam_3")) {
    current = false;
    node = get_node("../Table/BallMotion/BallCam");
    cam = Object::cast_to<Camera>(node);
    cam->set_current(true);
  }
}
