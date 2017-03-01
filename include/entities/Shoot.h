#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

#define PLAYER_SHOOT 1
#define ENEMY_SHOOT  2

class Shoot
{
public:
  Shoot(int shooter, Ogre::Vector3 coord, Ogre::SceneManager* sceneMgr);
  ~Shoot();
  bool checkCollition(Ogre::SceneNode * node);
  void updatePosition();

private:
  bool _valid = true;
  Ogre::Vector3 _position;
  Ogre::SceneNode * _node;
  Ogre::SceneManager * _sceneMgr;
  int _shooter;
};
