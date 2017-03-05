#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

class Enemy
{
public:
  Enemy(Ogre::SceneManager* sceneMgr);
  ~Enemy();
  void updatePosition(Ogre::Real deltaT);
  bool shoot();
  Ogre::Vector3 getPosition();
  Ogre::SceneNode * getSceneNode();

private:
  Ogre::Vector3 _position;
  Ogre::SceneNode * _node;
  Ogre::SceneManager * _sceneMgr;
  double getRandomXPosition();
};
