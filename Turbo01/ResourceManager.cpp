#include "ResourceManager.hpp"


ResourceManager::~ResourceManager() {
  for (auto& texture : textures_) {
    glDeleteTextures(1, &texture.second.second);
  }
}

void ResourceManager::LoadTexture(const std::string& filepath, TextureID id) {
  if (textures_.find(id) != textures_.end()) {
    return;
  }
  GLuint textureID = LoadTextureFromFile(filepath);
  textures_[id] = std::make_pair(filepath, textureID);
}

void ResourceManager::LoadModel(const std::string& filepath, ModelID id) {
  if (models_.find(id) != models_.end()) {
    return;
  }
  std::shared_ptr<GLMmodel> model = LoadModelFromFile(filepath);
  models_[id] = make_pair(filepath, model);
}

void ResourceManager::LoadResources() {
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  LoadTexture("Resources/Car/BlueCar/car.jpg", TextureID::BlueCar);
  LoadTexture("Resources/Car/BlackCar/car.jpg", TextureID::BlackCar);
  LoadTexture("Resources/GameWorld/img_road.jpg", TextureID::Road);
  LoadTexture("Resources/CarProperties/tyre.jpg", TextureID::Tyre);
  LoadTexture("Resources/Menu/MenuBackground.jpg", TextureID::MenuBackground);
  LoadTexture("Resources/Menu/menu11.jpg", TextureID::Menu1);
  LoadTexture("Resources/Menu/menu12.jpg", TextureID::Menu2);
  LoadTexture("Resources/intro/BackgroundIntro.jpg",
              TextureID::IntroBackground);
  LoadTexture("Resources/GameWorld/sand.jpg", TextureID::Sand);
  LoadTexture("Resources/GameWorld/sky.jpg", TextureID::Sky);
  LoadTexture("Resources/GameWorld/tree.jpg", TextureID::Tree);
  LoadTexture("Resources/CarProperties/speedometer.png",
              TextureID::SpeedoMeter);
  LoadTexture("Resources/CarProperties/pointer.png", TextureID::Pointer);
  LoadTexture("Resources/gameover.png", TextureID::GameOver);
  LoadTexture("Resources/winning.JPG", TextureID::WinGame);

  LoadModel("Resources/Car/BlackCar/car.obj", ModelID::BlackCar);
  LoadModel("Resources/Car/BlueCar/car.obj", ModelID::BlueCar);
  LoadModel("Resources/CarProperties/wheel.obj", ModelID::Wheel);
}

GLuint ResourceManager::GetTexture(TextureID id) {
  if (textures_.find(id) != textures_.end()) {
    return textures_[id].second;
  }
  return 0;
}

std::shared_ptr<GLMmodel> ResourceManager::GetModel(ModelID id) {
  if (models_.find(id) != models_.end()) {
    return models_[id].second;
  }
  return nullptr;
}

std::string ResourceManager::GetTextureFilePath(TextureID id) {
  return textures_[id].first;
}

std::string ResourceManager::GetModelFilePath(ModelID id) {
  return models_[id].first;
}

GLuint ResourceManager::LoadTextureFromFile(const std::string& filepath) {
  GLuint textureID = SOIL_load_OGL_texture(
      (char*)filepath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
      SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);
  if (textureID == 0) {
    std::cerr << "Failed to load texture: " << filepath << std::endl;
  }
  return textureID;
}

std::shared_ptr<GLMmodel> ResourceManager::LoadModelFromFile(
    const std::string& filepath) {
  GLMmodel* model = glmReadOBJ((char*)filepath.c_str());
  if (model == nullptr) {
    std::cerr << "Failed to load model: " << filepath << std::endl;
  }
  return std::shared_ptr<GLMmodel>(model,
                                   [](GLMmodel* model) { glmDelete(model); });
}
