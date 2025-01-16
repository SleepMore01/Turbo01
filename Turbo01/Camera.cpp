#include "Camera.hpp"

Camera::Camera() {
  m_RotationInY = 0;
  m_ElevationFromX = 21;
  m_CameraDistance = 10;
  m_UpCamera = -2;
}

void Camera::ChangeCamera(int x, int y) {
  static int prevx, prevy;
  int difx = x - prevx;
  int dify = y - prevy;
  prevx = x;
  prevy = y;

 if (difx > 0) {
    m_RotationInY++;
  } else if (difx < 0) {
    m_RotationInY--;
  }
  if (dify > 0) {
    m_ElevationFromX++;
  } else if (dify < 0) {
    m_ElevationFromX--;
  }

  if (m_ElevationFromX > 90) {
    m_ElevationFromX = 90;
  }
  if (m_ElevationFromX < 5) {
    m_ElevationFromX = 5;
  }
  if (m_CameraDistance < 5) {
    m_CameraDistance = 5;
  }
  if (m_CameraDistance > 20) {
    m_CameraDistance = 20;
  }
}

void Camera::OnMouseWheel(int button, int dir, int x, int y) {
  if (dir > 0) {
    m_CameraDistance--;
    ChangeCamera(0, 0);
  } else {
    m_CameraDistance++;
    ChangeCamera(0, 0);
  }
}

void Camera::UpCamera(float u) {
  m_UpCamera += u;
}
