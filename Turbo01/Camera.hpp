#pragma once

class Camera {
 public:
  Camera();
  //Camera(float, float, float );

 public:
  void ChangeCamera(int x, int y);

  float GetUpCamera() { return m_UpCamera; }
  void SetUpCamera(float val) { m_UpCamera = val; }

  float GetDistance() { return m_CameraDistance; }
  void SetCameraDistance(float val) { m_CameraDistance = val; }

  int GetRotationInY() { return m_RotationInY; }
  void SetRotationInY(int val) { m_RotationInY = val; }

  int GetElevationFromX() { return m_ElevationFromX; }
  void SetElevationFromX(int val) { m_ElevationFromX = val; }

  void OnMouseWheel(int button, int dir, int x, int y);

  void UpCamera(float u);

 public:
  int m_ElevationFromX;
  float m_UpCamera;
  float m_CameraDistance;
  int m_RotationInY;
};
