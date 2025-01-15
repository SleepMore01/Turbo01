#include "Camera.hpp"

Camera::Camera() {

}

void Camera::ChangeCamera(int x, int y) {
  static int prevx, prevy;
  int difx = x - prevx;
  int dify = y - prevy;
  prevx = x;
  prevy = y;

  if (difx > 0) {
    SetRotationInY(GetRotationInY() + 1);
  } else if (difx < 0) {
    SetRotationInY(GetRotationInY() - 1);
  }
  if (dify > 0) {
    SetElevationFromX(GetElevationFromX() + 1);
  } else if (dify < 0) {
    SetElevationFromX(GetElevationFromX() - 1);
  }

  if (GetElevationFromX() > 90) {
    SetElevationFromX(90);
  }
  if (GetElevationFromX() < 5) {
    SetElevationFromX(5);
  }
  if (GetCameraDistance() < 5) {
    SetCameraDistance(5);
  }
  if (GetCameraDistance() > 20) {
    SetCameraDistance(20);
  }
}


