#include "GameManager.hpp"

long GameManager::highScore_ = 0;

GameManager::GameManager()
    : windowHeight_(920), windowWidth_(1280), gameState_(GameState::Off) {}

void GameManager::initialize() {}

void GameManager::setWindowSize(int width, int height) {
  windowHeight_ = width;
  windowWidth_ = height;
}

std::pair<int, int> GameManager::getWindowSize() const {
  return {windowHeight_, windowWidth_};
}

GameState GameManager::getGameState() const {
  return gameState_;
}

void GameManager::setGameState(GameState state) {
  gameState_ = state;
}

void GameManager::LoadOrInitializeScore() {
  std::fstream file("score.txt",
                    std::ios::in | std::ios::out | std::ios::binary);

  if (file) {
    long score = 0;
    file.read(reinterpret_cast<char*>(&score), sizeof(long));
    GameManager::SetHighScore(score);
  } else {
    file.clear();
    file.open("score.txt", std::ios::out | std::ios::binary);

    if (file) {
      long initial_score = 0;
      file.write(reinterpret_cast<const char*>(&initial_score), sizeof(long));
    }
  }
  file.close();
}

long GameManager::GetHighScore() {
  return highScore_;
}

void GameManager::SetHighScore(long score) {
  highScore_ = score;
}