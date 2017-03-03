#include "Game.h"

Game::Game() {
  _points = 0;
}

Game::~Game () {
}

void Game::setPlayerName(std::string name) {
  _player = name;
}

std::string Game::getPlayerName() {
  return _player;
}

void Game::plusPoints() {
  /* code */
}

int Game::getPoints() {
  return _points;
}

void Game::restart() {
  _points = 0;
}
