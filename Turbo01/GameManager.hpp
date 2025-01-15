#pragma once

#include <array>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>>


enum class GameState { Off, Paused, Running, GameOver };


class GameManager {
 public:
  GameManager();
  void initialize();
  void setWindowSize(int width, int height);
  std::pair<int, int> getWindowSize() const;
  GameState getGameState() const;
  
  
  /*void printText(int x,
                 int y,
                 float r,
                 float g,
                 float b,
                 void* font,
                 const std::string& text);*/

  static long GetHighScore();
  static void SetHighScore(long score);

  void setGameState(GameState state);
  void static LoadOrInitializeScore();

 private:
  int windowHeight_;
  int windowWidth_;
  GameState gameState_;
  static long highScore_;
};
