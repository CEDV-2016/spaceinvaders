#pragma once

#include <Ogre.h>

#define MAX_ROLL 45
#define MAX_PITCH 35
#define TURN_DEGREE 4
#define INITIAL_LIFES 3

class Player
{
public:
  Player();
  ~Player();
  Ogre::Vector3 getPosition();
  Ogre::SceneNode * getSceneNode();
  void create(std::string color, Ogre::SceneManager * sceneMgr);
  void moveForward(Ogre::Real deltaT);
  void moveBackward(Ogre::Real deltaT);
  void moveRight(Ogre::Real deltaT);
  void moveLeft(Ogre::Real deltaT);
  void moveToInitialState(Ogre::Real deltaT);
  void setOrientation();
  void receiveShoot();
  int getLifes();

private:
  Ogre::Vector3 _position;
  Ogre::SceneNode * _node;
  Ogre::SceneManager * _sceneMgr;
  double _roll, _pitch;
  int _lifes;
};
