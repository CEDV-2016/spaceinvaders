#include "Player.h"

Player::Player()
{
  _position = Ogre::Vector3 ( 0, 1, 5 );
  _roll = _pitch = 0;
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

  if ( _pitch > -MAX_PITCH)
  {
    _pitch -= TURN_DEGREE;
    setOrientation();
  }
}

void Player::moveBackward()
{
  _position += Ogre::Vector3(0, 0, 0.05);
  _node->setPosition( _position );

  if ( _pitch < MAX_PITCH)
  {
    _pitch += TURN_DEGREE;
    setOrientation();
  }
}

void Player::moveRight()
{
  _position += Ogre::Vector3(0.05, 0, 0);
  _node->setPosition( _position );

  if ( _roll > -MAX_ROLL)
  {
    _roll -= TURN_DEGREE;
    setOrientation();
  }

}

void Player::moveLeft()
{
  _position += Ogre::Vector3(-0.05, 0, 0);
  _node->setPosition( _position );

  if ( _roll < MAX_ROLL)
  {
    _roll += TURN_DEGREE;
    setOrientation();
  }
}

void Player::moveToInitialState()
{
  if (_roll != 0)
  {
    if (_roll < 0)
    {
      _roll += TURN_DEGREE;
    }
    if (_roll > 0)
    {
      _roll -= TURN_DEGREE;
    }
  }

  if (_pitch != 0)
  {
    if (_pitch < 0)
    {
      _pitch += TURN_DEGREE;
    }
    if (_pitch > 0)
    {
      _pitch -= TURN_DEGREE;
    }
  }
  setOrientation();
}

void Player::setOrientation()
{
  _node->setOrientation(Ogre::Quaternion( Ogre::Degree(_pitch), Ogre::Vector3::UNIT_X) *
  Ogre::Quaternion( Ogre::Degree(0),      Ogre::Vector3::UNIT_Y) *
  Ogre::Quaternion( Ogre::Degree(_roll),  Ogre::Vector3::UNIT_Z) );
}
