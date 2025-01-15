#include "TurboGame.hpp"


float TurboGame::m_UpCamera;
float TurboGame::m_CameraDistance_;
int TurboGame::m_RotationInY;
int TurboGame::m_ElevationFromX;

int TurboGame::m_RightLeftKey = 0;
int TurboGame::m_UpDownKey = 0;
int TurboGame::m_TotalOpponentCars = 7;
int TurboGame::m_GameOver = 0;
long TurboGame::m_LastOpponentCarTime;
long TurboGame::m_LastSideCarTime;

int TurboGame::ttime;
int TurboGame::winningGame;

float TurboGame::pos = 0;
long TurboGame::score = 0;
long TurboGame::m_ElapsedTime, TurboGame::m_TotalTime;
double TurboGame::roadLoop;
int TurboGame::gamePlaying;

Car TurboGame::m_PlayerCar;
std::vector<Car> TurboGame::m_CompetitiveCars;
std::vector<Tree> TurboGame::m_TrackDecorations;

void TurboGame::EnterGame() {
  m_GameOver = 0;
  winningGame = 0;
  gamePlaying = 2;
  ttime = 300;
  glutSpecialFunc(GameSpecialKey);
  glutSpecialUpFunc(GameSpecialKeyUp);
  glutKeyboardFunc(GameAsciiKey);

  glutMouseFunc(GameMouse);
  glutMotionFunc(GameMouseMove);
  glutMouseWheelFunc(GameMouseWheel);

  
  glutDisplayFunc(RenderGame);

  roadLoop = 1.0;

  m_RotationInY = 0;
  m_ElevationFromX = 21;  
  m_CameraDistance_ = 10;  
  m_UpCamera = -2;
  
  GameChangeCamera(0, 0);

  m_TotalTime = 0;

  m_PlayerCar.SetCarTexture(TextureID::BlackCar);
  m_PlayerCar.SetCarTextureType(TextureID::BlackCar);
  m_PlayerCar.SetCarModelType(ModelID::BlackCar);

  m_PlayerCar.SetVelocity(1.0f);
  m_PlayerCar.SetAcceleration(0.03f);
  m_PlayerCar.SetPosition(glm::vec2(0.0f, 0.0f));
  m_PlayerCar.SetTyreRotation(0.0f);
  m_PlayerCar.SetRotation(0.0f);
  score = 0;

  m_LastOpponentCarTime = m_LastSideCarTime = m_TotalTime;

  GameLoop(42);
}

void TurboGame::GameLoop(int x) {
  if (gamePlaying == 2) {
    UpdateGameLogic();
    glutPostRedisplay();
    glutTimerFunc(1000.f / 30.f, GameLoop, 0);
  } else if (gamePlaying == 1) {
    glutPostRedisplay();
    glutTimerFunc(1000.f / 30.f, GameLoop, 0);
  }
}

void TurboGame::LeaveGame() {
  gamePlaying = 0;
  glutSpecialFunc(nullptr);
  glutSpecialUpFunc(nullptr);
  glutKeyboardFunc(nullptr);

  glutMouseFunc(nullptr);
  glutMotionFunc(nullptr);
  glutMouseWheelFunc(nullptr);

  m_CompetitiveCars.clear();
  m_TrackDecorations.clear();
}

void TurboGame::RenderGame() {
  glLoadIdentity();
  int i;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  glTranslated(0.0, 0.0, -m_CameraDistance_);
  glRotated(m_ElevationFromX, 1.0, 0.0, 0.0);
  glRotated(m_RotationInY, 0.0, 1.0, 0.0);

  glMatrixMode(GL_TEXTURE);
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_CULL_FACE);
  glColor3f(1, 1, 1);

  GLUquadricObj* qObj = gluNewQuadric();
  gluQuadricNormals(qObj, GLU_SMOOTH);
  gluQuadricTexture(qObj, GL_TRUE);
  glBindTexture(GL_TEXTURE_2D,
                ResourceManager::Instance().GetTexture(TextureID::Sky));
  glPushMatrix();
  glRotatef(180.0, 1.0, 0, 0);
  gluSphere(qObj, 80.0f, 24, 24);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  // Draw road

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);

  glTranslatef(0, roadLoop, 0);
  glBindTexture(GL_TEXTURE_2D,
                ResourceManager::Instance().GetTexture(TextureID::Road));

  glBegin(GL_QUADS);

  glColor3f(1, 1, 1);

  glTexCoord2f(0.0, 0.0);
  glVertex3d(4, 0, -200);

  glTexCoord2f(1.0, 0.0);
  glVertex3d(-4, 0, -200);

  glTexCoord2f(1.0, 4.0);
  glVertex3d(-4, 0, 200);

  glTexCoord2f(0.0, 4.0);
  glVertex3d(4, 0, 200);

  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D,
                ResourceManager::Instance().GetTexture(TextureID::Sand));
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex3f(-100.0, -0.3, -1000.0);
  glTexCoord2d(0.0, 50.0);
  glVertex3f(-100.0, -0.3, 1000.0);
  glTexCoord2d(10.0, 50.0);
  glVertex3f(100.0, -0.3, 1000.0);
  glTexCoord2d(10.0, 0.0);
  glVertex3f(100.0, -0.3, -1000.0);

  glEnd();
  glDisable(GL_TEXTURE_2D);
  // DEBUG_drwCord();

  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  std::reverse(m_TrackDecorations.begin(), m_TrackDecorations.end());

  for (const auto& tree : m_TrackDecorations) {
    RenderTree(tree);
  }
  m_PlayerCar.Render();

  for (auto car : m_CompetitiveCars) {
    car.Render();
  }

  glPopMatrix();

  glPushMatrix();
  glTranslated(0.0, 0.0, -9.0);
  glRotated(21.0, 1.0, 0.0, 0.0);
  glRotated(0, 0.0, 1.0, 0.0);

  RenderScore();

  RenderSpeedometer();
  if (m_GameOver == 1) {
    RenderGameOver();
  }
  if (winningGame == 1) {
    RenderWinning();
  }
  glPopMatrix();
  glutSwapBuffers();
}

void TurboGame::RenderScore() {
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);

  std::string sc = "Your score = " + std::to_string(score);
  std::string tc = "Target score = " + std::to_string(2025);
  std::string ttimee = "Time: = " + std::to_string(ttime); 

  TextRendering(5, 3, GLUT_BITMAP_HELVETICA_18, sc, 0, 255, 0, 1);
  TextRendering(5, 2, GLUT_BITMAP_HELVETICA_18, tc, 0, 255, 0, 1);
  TextRendering(5, 1, GLUT_BITMAP_HELVETICA_18, ttimee, 0, 0, 255,1);

  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
}

void TurboGame::RenderSpeedometer() {
  static float aaa = 0;
  if (aaa == 0.0)
    aaa = m_PlayerCar.GetVelocity();
  if (aaa > m_PlayerCar.GetVelocity()) {
    aaa -= 0.05;
  } else if (aaa < m_PlayerCar.GetVelocity()) {
    aaa += 0.05;
  }

  glPushMatrix();

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPushMatrix();
  glTranslatef(-4.0, -3.0, 0.0);
  glScalef(0.3, 0.3, 0.3);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,
                ResourceManager::Instance().GetTexture(TextureID::SpeedoMeter));
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex3f(-5.0, -5.0, 0);
  glTexCoord2d(0.0, 1.0);
  glVertex3f(-5.0, 5.0, 0.0);
  glTexCoord2d(1.0, 1.0);
  glVertex3f(5.0, 5.0, 0.0);
  glTexCoord2d(1.0, 0.0);
  glVertex3f(5.0, -5.0, 0.0);

  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  glPushMatrix();

  glTranslatef(-4.0, -3.0, 0.0);
  float deg = -aaa * 40 + 70;
  if (std::fabs(deg) > 150) {
    deg = 150;
  }
  glRotatef(deg, 0, 0, 1.0);
  glScalef(0.3, 0.3, 0.3);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,
                ResourceManager::Instance().GetTexture(TextureID::Pointer));
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex3f(-5.0, -5.0, 0);
  glTexCoord2d(0.0, 1.0);
  glVertex3f(-5.0, 5.0, 0.0);
  glTexCoord2d(1.0, 1.0);
  glVertex3f(5.0, 5.0, 0.0);
  glTexCoord2d(1.0, 0.0);
  glVertex3f(5.0, -5.0, 0.0);

  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

  glPopMatrix();
}

void TurboGame::RenderGameOver() {
  static float pqr = 1.0;
  if (pqr >= 0.2) {
    pqr -= 0.1;
  }

  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glBindTexture(GL_TEXTURE_2D,
                ResourceManager::Instance().GetTexture(TextureID::GameOver));

  glScalef(pqr, pqr, 1.0);

  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex3f(-20.0, -5.0, 3.0);
  glTexCoord2d(0.0, 1.0);
  glVertex3f(-20.0, 5.0, 3.0);
  glTexCoord2d(1.0, 1.0);
  glVertex3f(20.0, 5.0, 3.0);
  glTexCoord2d(1.0, 0.0);
  glVertex3f(20.0, -5.0, 3.0);

  glEnd();

  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  glPopMatrix();
}

void TurboGame::RenderWinning() {
  static float pqr = 1.0;
  if (pqr >= 0.2) {
    pqr -= 0.1;
  }

  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glBindTexture(GL_TEXTURE_2D,
                ResourceManager::Instance().GetTexture(TextureID::WinGame));

  glScalef(pqr, pqr, 1.0);

  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex3f(-20.0, -5.0, 3.0);
  glTexCoord2d(0.0, 1.0);
  glVertex3f(-20.0, 5.0, 3.0);
  glTexCoord2d(1.0, 1.0);
  glVertex3f(20.0, 5.0, 3.0);
  glTexCoord2d(1.0, 0.0);
  glVertex3f(20.0, -5.0, 3.0);

  glEnd();

  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  glPopMatrix();
}

void TurboGame::UpdateGameLogic() {
  m_ElapsedTime = 1000.f / 30.f;
  m_TotalTime += m_ElapsedTime;
  ttime--;

  UpdateOpponentCars();
  UpdateSideObjects();
  UpdatePlayerCar();

  for (const auto& CurCar : m_CompetitiveCars) {
    if (std::fabs(CurCar.GetPosition().x - m_PlayerCar.GetPosition().x) < 2) {
      if (std::fabs(CurCar.GetPosition().y - m_PlayerCar.GetPosition().y) <
          4.5) {
        OnGameOver();

        m_PlayerCar.SetVelocity(0.0f);
        if (score > GameManager::GetHighScore()) {
          GameManager::SetHighScore(score);

          const std::filesystem::path filePath = "score.txt";
          std::ofstream file(filePath, std::ios::binary);
          if (!file) {
            std::cerr << "Failed to open the file for writing.\n";
            exit(0);
          }
          file.write(reinterpret_cast<const char*>(&score), sizeof(score));
          if (file.good()) {
            std::cout << "Score written successfully.\n";
          } else {
            std::cerr << "Failed to write to the file.\n";
          }
        }
        break;
      }
    }
  }

  if (score >= 2025) {
    winningGame = 1;
    gamePlaying = 1;
  }

  if (ttime <= 0) {
    OnGameOver();
  }
}

void TurboGame::UpdatePlayerCar() {
  m_PlayerCar.IncreaseVelocity(m_PlayerCar.GetAcceleration() * (m_ElapsedTime / 1000.0));

  float dist = m_PlayerCar.GetVelocity() * (m_ElapsedTime / 1000.0);
  score += (int)(dist * 100);

  m_PlayerCar.IncreaseTyreRotation(((dist) / (2.0 * 3.1415 * .01)) * 360.0f);
  while (m_PlayerCar.GetTyreRotation() > 360.0) {
    m_PlayerCar.IncreaseTyreRotation(-360.0f);
  }
  roadLoop -= dist;

  if (roadLoop < 0.0)
    roadLoop = (1 + roadLoop);


  
   // Collision Detection ROAD
  if ((m_RightLeftKey) && (std::fabs(m_PlayerCar.GetPosition().x) < 3)) {
    m_PlayerCar.IncreasePosition(glm::vec2(m_RightLeftKey * 0.3f, 0.0f));
    m_PlayerCar.IncreaseRotation(m_RightLeftKey * 4.f);

    if (std::fabs(m_PlayerCar.GetRotation()) > Car::GetMaximumCarRotation()) {
      m_PlayerCar.SetRotation(
          ((m_PlayerCar.GetRotation() < 0) ? -1 : 1) * Car::GetMaximumCarRotation());
    }

    if (std::fabs(m_PlayerCar.GetPosition().x) >
        Car::GetMaximumCarSidePosition()) {
      OnGameOver();
      m_PlayerCar.SetPosition(glm::vec2(((m_PlayerCar.GetPosition().x < 0) ? -1 : 1) *
                             (Car::GetMaximumCarSidePosition() - 0.01f), m_PlayerCar.GetPosition().y));
    }
  }



  if ((!m_RightLeftKey) && (std::fabs(m_PlayerCar.GetRotation()) > 0.1)) {
    m_PlayerCar.IncreaseRotation(((m_PlayerCar.GetRotation() > 0) ? -1 : 1) *
                                 4.f);
    if (std::fabs(m_PlayerCar.GetRotation()) < 5)
      m_PlayerCar.SetRotation(0.0f);
  }
}

void TurboGame::UpdateOpponentCars() {
  int i;
  if (m_CompetitiveCars.size() < m_TotalOpponentCars) {
    if (m_TotalTime - m_LastOpponentCarTime > 2000) {
      srand(time(0));
      if ((rand() % m_TotalOpponentCars) <=
          (m_TotalOpponentCars - (int)m_CompetitiveCars.size())) {
        m_LastOpponentCarTime = m_TotalTime;
        Car newCar;
        newCar.SetPosition(glm::vec2(((rand() % 6) - 3), 100.f));
        newCar.SetVelocity((1.0 * m_PlayerCar.GetVelocity()) / 3.0f);
        newCar.SetAcceleration(0.0f);

        newCar.SetCarTexture(TextureID::BlueCar);
        newCar.SetCarTextureType(TextureID::BlueCar);
        newCar.SetCarModelType(ModelID::BlueCar);

        newCar.SetRotation(0.0f);
        newCar.SetTyreRotation(0.0f);

        i = rand() % 2;
        switch (i) {
          case 0:
            newCar.SetCarType(CarType::ConstantVelocity);
            break;
          case 1:
            newCar.SetCarType(CarType::ConstantVelocityMoving);
            newCar.state1 = (newCar.GetPosition().x > 0) ? 0 : 1;
            break;
        }
        m_CompetitiveCars.push_back(newCar);
      }
    }
  }
  for (auto& car : m_CompetitiveCars) {
    float dist;
    car.IncreaseVelocity(car.GetAcceleration() * (m_ElapsedTime / 1000.0));

    dist =
        (m_PlayerCar.GetVelocity() - car.GetVelocity() * (m_ElapsedTime / 15.0));
    car.IncreasePosition(glm::vec2(0.0f, - std::fabs(dist)));

    car.IncreaseTyreRotation(((std::fabs(dist)) / (2.0 * 3.1415 * .04)) * 360.0);

    while (car.GetTyreRotation() > 360.0) {
      car.IncreaseTyreRotation(-360.0f);
    }

    if (car.GetCarType() == CarType::ConstantVelocityMoving) {
      if (car.state1 == 0) {
        car.IncreasePosition(glm::vec2(-0.17, 0.0f));
        if (car.GetPosition().x < -2.7) {
          car.state1 = 1;
        }
      } else {
        car.IncreasePosition(glm::vec2(0.17, 0.0f));
        if (car.GetPosition().x > 2.7) {
          car.state1 = 0;
        }
      }
    }
  }

  while (!m_CompetitiveCars.empty() &&
         m_CompetitiveCars.back().GetPosition().y < -100) {
    m_CompetitiveCars.pop_back();
  }
}

void TurboGame::UpdateSideObjects() {
  int i;
  if (m_TotalTime - m_LastSideCarTime > 20) {
    srand(m_TotalTime);
    if ((rand() % 2) < 1) {
      m_LastSideCarTime = m_TotalTime;

      Tree obj{};

      if (rand() % 2 == 0) {
        obj.x =
            15 + (sin(rand() % 90 * (float)std::numbers::pi / 180.0f) * 30.0f);
      } else {
        obj.x =
            -15 - (sin(rand() % 90 * (float)std::numbers::pi / 180.0f) * 30.0f);
      }
      obj.y = 200;
      // m_TrackDecorations.push_back(obj);
    }
  }
  for (auto& curTree : m_TrackDecorations) {
    float dist = m_PlayerCar.GetVelocity() * m_ElapsedTime / 15.0;
    curTree.y -= std::fabs(dist);
  }
  while (!m_TrackDecorations.empty() && m_TrackDecorations.back().y < -20) {
    m_TrackDecorations.pop_back();
  }
}

void TurboGame::GameSpecialKey(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      m_PlayerCar.IncreaseVelocity(1.f);
      m_UpDownKey = 1;

      break;
    case GLUT_KEY_DOWN:
      m_PlayerCar.IncreaseVelocity(-0.5f);
      m_UpDownKey = -1;

      break;
    case GLUT_KEY_LEFT:
      m_RightLeftKey = -1;

      break;
    case GLUT_KEY_RIGHT:
      m_RightLeftKey = 1;
      break;
  }
}

void TurboGame::GameSpecialKeyUp(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      m_PlayerCar.IncreaseVelocity(-1.f);
      m_UpDownKey = 0;
      break;
    case GLUT_KEY_DOWN:
      m_PlayerCar.IncreaseVelocity(0.5f);
      m_UpDownKey = 0;
      break;
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
      m_RightLeftKey = 0;
      break;
  }
}

void TurboGame::GameAsciiKey(unsigned char key, int x, int y) {
  if (m_GameOver == 1 || winningGame == 1) {
    if (key == 13) {
      LeaveGame();
      MainMenu::Enter();
    }
    return;
  }
  switch (key) {
    case 27:
      break;
    case 'w':
      m_UpCamera -= 0.1;
      GameChangeCamera(0, 0);
      break;
    case 's':
      m_UpCamera += 0.1;
      GameChangeCamera(0, 0);
      break;
    case 'p':
      gamePlaying = (gamePlaying == 2) ? 1 : 2;
      break;
    default:
      break;
  }
}

void TurboGame::GameMouse(int button, int state, int x, int y) {
  // nothing to do here
}

void TurboGame::GameMouseWheel(int button, int dir, int x, int y) {
  if (dir > 0) {
    m_CameraDistance_--;
    GameChangeCamera(0, 0);
  } else {
    m_CameraDistance_++;
    GameChangeCamera(0, 0);
  }
}

void TurboGame::GameMouseMove(int x, int y) {
  GameChangeCamera(x, y);
}

void TurboGame::OnGameOver() {
  gamePlaying = 1;
  m_GameOver = 1;
}

void TurboGame::GameChangeCamera(int x, int y) {
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
  if (m_CameraDistance_ < 5) {
    m_CameraDistance_ = 5;
  }
  if (m_CameraDistance_ > 20) {
    m_CameraDistance_ = 20;
  }
}

void TurboGame::TextRendering(float x,
                              float y,
                              LPVOID font,
                              const std::string_view& text,
                              float red,
                              float green,
                              float blue,
                              float alpha) {
  if (text.empty()) {
    return;
  }
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(red, green, blue, alpha);
  glRasterPos3f(x, y, -m_CameraDistance_);

  for (const char& ch : text) {
    glutBitmapCharacter(font, static_cast<int>(ch));
  }
  glDisable(GL_BLEND);
}

void TurboGame::RenderTree(Tree tree) {
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glTranslatef(tree.x, -1.0, -tree.y);

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glRotatef(45.0, 0, 1.0, 0);
  glBindTexture(GL_TEXTURE_2D,
                ResourceManager::Instance().GetTexture(TextureID::Tree));
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex3f(-5.0, -5.0, 0);
  glTexCoord2d(0.0, 1.0);
  glVertex3f(-5.0, 5.0, 0.0);
  glTexCoord2d(1.0, 1.0);
  glVertex3f(5.0, 5.0, 0.0);
  glTexCoord2d(1.0, 0.0);
  glVertex3f(5.0, -5.0, 0.0);

  glEnd();
  glPushMatrix();
  glRotatef(90.0, 0, 1.0, 0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex3f(-5.0, -5.0, 0);
  glTexCoord2d(0.0, 1.0);
  glVertex3f(-5.0, 5.0, 0.0);
  glTexCoord2d(1.0, 1.0);
  glVertex3f(5.0, 5.0, 0.0);
  glTexCoord2d(1.0, 0.0);
  glVertex3f(5.0, -5.0, 0.0);

  glEnd();
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glPopMatrix();
}