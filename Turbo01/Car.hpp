#pragma once

#include <GL/freeglut.h>
#include <glm/vec2.hpp>
#include <memory>
#include "ResourceManager.hpp"

enum CarType { ConstantVelocity, ConstantVelocityMoving };

class Car {
 public:
  explicit Car();
  void Render();

  inline GLuint GetCarTexture() const { return m_CarTexture; }
  inline void SetCarTexture(TextureID carID) {
    ResourceManager::Instance().GetTexture(carID);
  }

  inline float GetVelocity() const { return m_Velocity; }
  inline void SetVelocity(float newVelocity) { m_Velocity = newVelocity; }

  inline float GetAcceleration() const { return m_Acceleration; }
  inline void SetAcceleration(float newAcceleration) {
    m_Acceleration = newAcceleration;
  }

  static constexpr float GetMaximumCarRotation() { return 15.0f; }
  static constexpr float GetMaximumCarSidePosition() { return 3.0f; }

  inline glm::vec2 GetPosition() const { return m_Position; }
  inline void SetPosition(const glm::vec2& newPosition) {
    m_Position = newPosition;
  }

  inline float GetRotation() const { return m_Rotation; }
  inline void SetRotation(float newRotation) { m_Rotation = newRotation; }

  inline void SetCarType(CarType carType) { m_CarType = carType; }
  inline CarType GetCarType() const { return m_CarType; }

  inline TextureID GetCarTextureType() const { return m_CarTextureType; }
  inline void SetCarTextureType(TextureID carTextureType) {
    m_CarTextureType = carTextureType;
  }




  inline ModelID GetCarModelType() const { return m_CarModelType; }
  inline void SetCarModelType(ModelID carModelType) {
    m_CarModelType = carModelType;
  }

  inline float GetTyreRotation() const { return m_TyreRotation; }
  inline void SetTyreRotation(float newTyreRotation) {
    m_TyreRotation = newTyreRotation;
  }

  void IncreasePosition(glm::vec2 pos);
  void IncreaseVelocity(float vel);
  void IncreaseRotation(float rot);
  void IncreaseTyreRotation(float tyreRot);
  int state1, state2, state3;

 private:
  glm::vec2 m_Position;
  float m_Rotation;
  GLuint m_CarTexture;
  float m_Velocity;
  float m_Acceleration;
  float m_TyreRotation;
  CarType m_CarType;
  

  TextureID m_CarTextureType;
  ModelID m_CarModelType;
};
