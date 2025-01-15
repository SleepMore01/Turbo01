#pragma once

#include <GL/freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <string>
#include <string_view>

#include "ResourceManager.hpp"
#include "GameManager.hpp"
#include "MainMenu.hpp"
#include "TurboGame.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct WindowSpecification {
  static inline int Width = 1080;
  static inline int Height = 720;
  static constexpr std::string_view Title = "Turbo01";

  static inline double Ratio =
      static_cast<double>(Width) / static_cast<double>(Height);
};

class Application {	
 public:
  Application(int argc, char** argv);

  void Run();

 private:
  void Initialization(int argc, char** argv);
  void static OnWindowResize(int width, int height);

 private:
};