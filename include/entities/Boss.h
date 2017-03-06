#pragma once

#include <Ogre.h>

#define MOVE_RIGHT 0
#define MOVE_LEFT  1
#define BOSS_LIFE  20
#define MAX_ROLL_BOSS 10
#define TURN_DEGREE_BOSS 0.5

class Boss
{
public:
  Boss();
  ~Boss();
  void create(Ogre::SceneManager* sceneMgr);
  void updatePosition(Ogre::Real deltaT);
  void setOrientation();
  bool shoot();
  Ogre::Vector3 getPosition();
  Ogre::SceneNode * getSceneNode();
  void receiveShoot();
  bool isAlive();

private:
  Ogre::Vector3 _position;
  Ogre::SceneNode * _node;
  Ogre::SceneManager * _sceneMgr;

  int _move_towards;
  int _lifes;
  double _roll;
};
