#include "Enemy.h"
#include <iostream>

Enemy::Enemy(Ogre::SceneManager* sceneMgr)
{
  _sceneMgr = sceneMgr;

  int min_x = -10, max_x = 10;
  int rand_x = rand() % (max_x - min_x + 1) + min_x;

  _position = Ogre::Vector3 (rand_x, 0, -15);

  Ogre::Entity * entity = _sceneMgr->createEntity("Enemy.mesh");
  _node = _sceneMgr->createSceneNode();
  _node->attachObject(entity);
  _node->setPosition(_position);
  _sceneMgr->getRootSceneNode()->addChild(_node);
}

Enemy::~Enemy() {}

void Enemy::updatePosition()
{
  if (_position.z > 15)
  {
    int min_x = -10, max_x = 10;
    int rand_x = rand() % (max_x - min_x + 1) + min_x;
    _position = Ogre::Vector3 (rand_x, 0, -15);
  }
  else
  {
    _position += Ogre::Vector3(0, 0, 0.02);
  }
  _node->setPosition(_position);
}

bool Enemy::shoot()
{
  int min = 0, max = 1000, probability = 2;

  int randNum = rand()%(max-min + 1) + min;

  return randNum <= probability;
}

Ogre::Vector3 Enemy::getPosition()
{
  return _position;
}
