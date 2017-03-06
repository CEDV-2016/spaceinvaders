#include "Shoot.h"
#include "SoundFXManager.h"

Shoot::Shoot(int shooter, Ogre::Vector3 position, Ogre::SceneManager* sceneMgr)
{
  _sceneMgr = sceneMgr;
  _shooter = shooter;
  _node = NULL;
  
  Ogre::Entity * ent_shoot = _sceneMgr->createEntity("Shoot.mesh");

  if (_shooter == ENEMY_SHOOT)
  {
    ent_shoot->setMaterialName("EnemyShoot.material");
  }

  if ( _shooter == PLAYER_SHOOT)
  {
    SoundFXManager::getSingletonPtr()->load("shoot.wav")->play();
  }
  _node = _sceneMgr->createSceneNode();
  _node->attachObject(ent_shoot);
  _node->setPosition(position);
  _sceneMgr->getRootSceneNode()->addChild(_node);
}

Shoot::~Shoot() { }

bool Shoot::updatePosition(Ogre::Real deltaT)
{
  if (_valid && _node)
  {
    switch(_shooter)
    {
      case PLAYER_SHOOT:
      if (_node->getPosition().z < -35)
      {
        destroyShoot();
      }
      else
      {
        _node->translate(0, 0, -0.4 * deltaT); //move up
      }
      break;

      case ENEMY_SHOOT:
      if (_node->getPosition().z > 30)
      {
        destroyShoot();
      }
      else
      {
        _node->translate(0, 0, 0.4 * deltaT); //move down
      }
      break;
    }
  }
  return _valid;
}


void Shoot::destroyShoot()
{
  _valid = false;
  if (_node)
  {
    _sceneMgr->destroySceneNode(_node);
    _node = NULL;
  }
}


bool Shoot::checkCollition(Ogre::SceneNode * node)
{
  float x_margin = 1.15, z_margin = 0.45;
  if (_valid && _node)
  {
    Ogre::Vector3 spaceship_position = node->getPosition();

    Ogre::Vector3 my_position;
    if (_node) my_position = _node->getPosition();
    else return false;

    if ( fabs( my_position.z - spaceship_position.z ) <= z_margin ) //checks Z axis
    {
      if ( fabs( my_position.x - spaceship_position.x ) <= x_margin ) //checks X axis
      {
        destroyShoot();
        return true;
      }
    }
  }
  return false;
}
