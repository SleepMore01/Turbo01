#pragma once

#include <GL/freeglut.h>
#include <SOIL.h>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "glm.hpp"

constexpr int DEFAULT_FPS = 30;
constexpr int FRAME_DELAY_MS = 1000 / DEFAULT_FPS;



enum class TextureID {
  BlackCar,
  BlueCar,
  Road,
  Tyre,
  MenuBackground,
  Menu1,
  Menu2,
  Intro,
  Sand,
  Sky,
  Tree,
  SpeedoMeter,
  Pointer,
  GameOver,
  WinGame,
  IntroBackground,
};

enum class ModelID { BlackCar, BlueCar, Tree, Wheel, Tyre };


class ResourceManager {
 public:
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  static ResourceManager& Instance() {
    static ResourceManager instance;
    return instance;
  }

  void LoadResources();

  GLuint GetTexture(TextureID);
  std::shared_ptr<GLMmodel> GetModel(ModelID id);

  std::string GetTextureFilePath(TextureID id);
  std::string GetModelFilePath(ModelID id);

 private:
  ResourceManager() = default;
  ~ResourceManager();

  std::unordered_map<TextureID, std::pair<std::string, GLuint>> textures_;
  std::unordered_map<ModelID, std::pair<std::string, std::shared_ptr<GLMmodel>>>
      models_;

  void LoadTexture(const std::string& filepath, TextureID id);
  void LoadModel(const std::string& filepath, ModelID id);

  GLuint LoadTextureFromFile(const std::string& filepath);
  std::shared_ptr<GLMmodel> LoadModelFromFile(const std::string& filepath);
};