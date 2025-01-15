#include "Car.hpp"

extern float car_crash_angle = 0.0;

Car::Car() {

}


void Car::Render() {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glRotatef(car_crash_angle, 1.0, 0, 0);
	glTranslatef(m_Position.x, 0.6, -m_Position.y);
	glRotatef(-m_Rotation, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::Instance().GetTexture(m_CarTextureType));
	glmDraw(ResourceManager::Instance().GetModel(m_CarModelType).get(), GLM_SMOOTH | GLM_TEXTURE);


	glRotated(-90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::Instance().GetTexture(TextureID::Tyre));


	glPushMatrix();
	glTranslatef(-1.205, -0.277, 0.733);
	glRotatef(-(m_Rotation * 2) + 90, 0, 1, 0);
	glRotatef(m_TyreRotation, -1, 0, 0);
	glmDraw(ResourceManager::Instance().GetModel(ModelID::Wheel).get(), GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.206, -0.277, -0.731);
	glRotatef(-(m_Rotation * 2) + 270, 0, 1, 0);
	glRotatef(m_TyreRotation, 1, 0, 0);
	glmDraw(ResourceManager::Instance().GetModel(ModelID::Wheel).get(), GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.155, -0.277, 0.731);
	glRotatef(90, 0, 1, 0);
	glRotatef(m_TyreRotation, -1, 0, 0);
	glmDraw(ResourceManager::Instance().GetModel(ModelID::Wheel).get(), GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.154, -0.277, -0.733);
	glRotatef(270, 0, 1, 0);
	glRotatef(m_TyreRotation, 1, 0, 0);
	glmDraw(ResourceManager::Instance().GetModel(ModelID::Wheel).get(), GLM_SMOOTH | GLM_TEXTURE);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Car::IncreasePosition(glm::vec2 pos) {
  m_Position += pos;
}

void Car::IncreaseRotation(float rot) {
  m_Rotation += rot;
}

void Car::IncreaseVelocity(float vel) {
  m_Velocity += vel;
}

void Car::IncreaseTyreRotation(float tyreRot) {
  m_TyreRotation += tyreRot;
}
