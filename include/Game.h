#ifndef Game_H
#define Game_H

#include <string>

class Game
{
private:
 int _points;
 std::string _player;

public:
  Game();
  ~Game ();
  void setPlayerName(std::string name);
  std::string getPlayerName();
  void plusPoints ();
  int getPoints();
  void restart();
};

#endif
