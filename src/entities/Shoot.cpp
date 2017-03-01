#include "Shoot.h"

Shoot::Shoot(int shooter, Ogre::Vector3 position, Ogre::SceneManager* sceneMgr)
{
  _sceneMgr = sceneMgr;
  _shooter = shooter;

  Ogre::Entity * ent_shoot = _sceneMgr->createEntity("Shoot.mesh");

  if (_shooter == ENEMY_SHOOT) {
    ent_shoot->getSubEntity(0)->setMaterialName("green_shoot");
  }

  _node = _sceneMgr->createSceneNode();
  _node->attachObject(ent_shoot);
  _node->setPosition(position);
  _sceneMgr->getRootSceneNode()->addChild(_node);
}

Shoot::~Shoot() { }

void Shoot::updatePosition()
{
  if (_valid)
  {
    switch(_shooter)
    {
      case PLAYER_SHOOT:
      if (_node->getPosition().z < -35) {
        _valid = false;
        _sceneMgr->destroySceneNode(_node);
      }
      else _node->translate(0, 0, -0.04); //move up
      break;

      case ENEMY_SHOOT:
      if (_node->getPosition().z > 30) {
        _valid = false;
        _sceneMgr->destroySceneNode(_node);
      }
      else _node->translate(0, 0, 0.04); //move down
      break;
    }
  }
}

bool Shoot::checkCollition(Ogre::SceneNode * node)
{
  if (_valid)
  {
     return false;
  }
  else return false;
}
