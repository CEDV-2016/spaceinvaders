#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

class Player
{
public:
  Player();
  ~Player();
  Ogre::Vector3 getPosition();
  Ogre::SceneNode * getSceneNode();
  void create(Ogre::SceneManager * sceneMgr);
  void moveForward();
  void moveBackward();
  void moveRight();
  void moveLeft();

private:
  Ogre::Vector3 _position;
  Ogre::SceneNode * _node;
  Ogre::SceneManager * _sceneMgr;
};
