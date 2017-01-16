#include "Game.hpp"

Game::Game() {

}

Game::~Game () {

}

int Game::getState() {
  return _state;
}

void Game::setState (int state) {
  _state = state;
}

void Game::restart() {
}
