#pragma once

#include <Ogre.h>

#define RIGHT 0
#define LEFT  1
#define BOSS_LIFE  20
#define MAX_ROLL 10
#define TURN_DEGREE 0.05

class Boss
{
public:
  Boss();
  ~Boss();
  void create(Ogre::SceneManager* sceneMgr);
  void updatePosition();
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
