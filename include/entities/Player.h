#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

#define MAX_ROLL 45
#define MAX_PITCH 35
#define TURN_DEGREE 0.5
#define INITIAL_LIFES 3

class Player
{
public:
  Player();
  ~Player();
  Ogre::Vector3 getPosition();
  Ogre::SceneNode * getSceneNode();
  void create(std::string color, Ogre::SceneManager * sceneMgr);
  void moveForward();
  void moveBackward();
  void moveRight();
  void moveLeft();
  void moveToInitialState();
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
