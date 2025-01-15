#include "Application.hpp"

Application::Application(int argc, char** argv) {
  Initialization(argc, argv);
}

void Application::Run() {
  glutMainLoop();
}

void Application::Initialization(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(WindowSpecification::Width, WindowSpecification::Height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(WindowSpecification::Title.data());

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  ResourceManager::Instance().LoadResources();

  MainMenu::Enter();
  glutReshapeFunc(OnWindowResize);

  GameManager::LoadOrInitializeScore();
}

void Application::OnWindowResize(int width, int height) {
  WindowSpecification::Width = width;
  WindowSpecification::Height = height;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double nearr = 1.0;
  double farr = 100.0;

  gluPerspective(45.0, WindowSpecification::Ratio, nearr, farr);

  glMatrixMode(GL_MODELVIEW);

  if (TurboGame::GetGamePlaying() > 0) {
    TurboGame::GameChangeCamera(0, 0); 
  }
}
