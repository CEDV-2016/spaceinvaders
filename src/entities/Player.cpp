#include "Player.h"

Player::Player()
{
  _position = Ogre::Vector3 ( 0, 1, 5 );
}

Player::~Player(){}

Ogre::Vector3 Player::getPosition()
{
  return _position;
}

Ogre::SceneNode * Player::getSceneNode()
{
  return _node;
}

void Player::create(Ogre::SceneManager * sceneMgr)
{
  _sceneMgr = sceneMgr;

  Ogre::Entity * entity = _sceneMgr->createEntity("Spaceship.mesh");
  entity->setCastShadows(true);
  _node = _sceneMgr->createSceneNode("Spaceship");
  _node->attachObject(entity);
  _node->setPosition(_position);
  _sceneMgr->getRootSceneNode()->addChild(_node);
}

void Player::moveForward()
{
  _position += Ogre::Vector3(0, 0, -0.05);
  _node->setPosition( _position );
}

void Player::moveBackward()
{
  _position += Ogre::Vector3(0, 0, 0.05);
  _node->setPosition( _position );
}

void Player::moveRight()
{
  _position += Ogre::Vector3(0.05, 0, 0);
  _node->setPosition( _position );
}

void Player::moveLeft()
{
  _position += Ogre::Vector3(-0.05, 0, 0);
  _node->setPosition( _position );
}
