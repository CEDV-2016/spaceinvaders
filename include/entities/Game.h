#ifndef Game_H
#define Game_H

#include <string>

#define NUMBER_ENEMIES  15
#define POINTS_ENEMY    10

class Game
{
private:
 int _points;
 int _enemies_left;
 std::string _player;

public:
  Game();
  ~Game ();
  static const int INITIAL_ENEMIES = 3;
  void setPlayerName(std::string name);
  std::string getPlayerName();
  int getPoints();
  void restart();
  void createEnemy();
  void destroyEnemy();
  bool enemiesLeft();
};

#endif
