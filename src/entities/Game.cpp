#include "Game.h"

Game::Game() {
  _points = 0;
  _enemies_left = NUMBER_ENEMIES;
}

Game::~Game () {}

void Game::setPlayerName(std::string name)
{
  _player = name;
}

std::string Game::getPlayerName()
{
  return _player;
}

int Game::getPoints()
{
  return _points;
}

void Game::restart()
{
  _points = 0;
}

void Game::createEnemy()
{
  _enemies_left--;
}

void Game::destroyEnemy()
{
  _points += POINTS_ENEMY;
}

bool Game::enemiesLeft()
{
  return _enemies_left > 0;
}
