#pragma once

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numbers>
#include <vector>
#include <utility>   
#include <functional>

#include "ResourceManager.hpp"
#include "MainMenu.hpp"
#include "Tree.hpp"
#include "GameManager.hpp"
#include "Car.hpp"
#include "Camera.hpp"


class TurboGame {
 public:
  TurboGame(const TurboGame&) = delete;
  TurboGame& operator=(const TurboGame&) = delete;
  ~TurboGame() = default;


   static TurboGame& Instance() {
    static TurboGame instance;
    return instance;
  }

   void EnterGame();

  void static GameLoop(int x);
  void static LeaveGame();
  // void static PauseGame();
  // void static ResumeGame();

  void static RenderGame();
  void static RenderScore();
  void static RenderSpeedometer();
  void static RenderGameOver();
  void static RenderWinning();
  void static RenderTree(Tree tree);

  void static UpdateGameLogic();
  void static UpdatePlayerCar();
  void static UpdateOpponentCars();
  void static UpdateSideObjects();


  void static GameSpecialKey(int key, int x, int y);
  void static GameSpecialKeyUp(int key, int x, int y);
  void static GameAsciiKey(unsigned char key, int x, int y);
  void static GameMouse(int button, int state, int x, int y);
  void static OnGameMouseWheel(int button, int dir, int x, int y);
  void static GameMouseMove(int x, int y);

  void static OnGameOver();

  void static GameChangeCamera(int x, int y);

  

  void static TextRendering(float x,
                    float y,
                    LPVOID font,
                    const std::string_view& text,
                    float r,
                    float g,
                    float b,
                    float a);

  inline int static GetGamePlaying() { return gamePlaying; }

 private:
  TurboGame() = default;
 
  int static m_RightLeftKey;
  int static m_UpDownKey;
  int static m_TotalOpponentCars;
  int static m_GameOver;
  long static m_LastOpponentCarTime; 
  long static m_LastSideCarTime;

  float static pos;
  static int ttime; 
  static int winningGame; 
  long static score;

  long static m_ElapsedTime, m_TotalTime; 

  double static roadLoop;

  int static gamePlaying;

  static Car m_PlayerCar;
  static std::vector<Car> m_CompetitiveCars;
  static std::vector<Tree> m_TrackDecorations;

  Camera m_GameCamera;
};
