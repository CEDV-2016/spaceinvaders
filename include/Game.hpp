#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Game
{
private:
  int _state, _points;

public:
  Game();
  ~Game ();
  int getState ();
  void setState (int state);
  void restart();
};
