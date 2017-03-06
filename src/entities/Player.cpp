#include "Player.h"
#include "SoundFXManager.h"

Player::Player() {}

Player::~Player() {}

Ogre::Vector3 Player::getPosition()
{
  return _position;
}

Ogre::SceneNode * Player::getSceneNode()
{
  return _node;
}

void Player::create(std::string color, Ogre::SceneManager * sceneMgr)
{
  _sceneMgr = sceneMgr;
  _position = Ogre::Vector3 ( 0, 1, 5 );
  _roll = _pitch = 0;
  _lifes = INITIAL_LIFES;

  Ogre::Entity * entity = _sceneMgr->createEntity("Spaceship.mesh");
  entity->setMaterialName(color);
  entity->setCastShadows(true);
  _node = _sceneMgr->createSceneNode("Spaceship");
  _node->attachObject(entity);
  _node->setPosition(_position);
  _sceneMgr->getRootSceneNode()->addChild(_node);
}

void Player::moveForward(Ogre::Real deltaT)
{
  if (_position.z < 15)
  {
    _position += Ogre::Vector3(0, 0, -0.5 * deltaT);
    _node->setPosition( _position );

    if ( _pitch > -MAX_PITCH)
    {
      _pitch -= TURN_DEGREE * deltaT;
      setOrientation();
    }
  }
}

void Player::moveBackward(Ogre::Real deltaT)
{
  if (_position.z > -15)
  {
    _position += Ogre::Vector3(0, 0, 0.5 * deltaT);
    _node->setPosition( _position );

    if ( _pitch < MAX_PITCH)
    {
      _pitch += TURN_DEGREE * deltaT;
      setOrientation();
    }
  }
}

void Player::moveRight(Ogre::Real deltaT)
{
  if (_position.x < 15)
  {
    _position += Ogre::Vector3(0.5 * deltaT, 0, 0);
    _node->setPosition( _position );

    if ( _roll > -MAX_ROLL)
    {
      _roll -= TURN_DEGREE * deltaT;
      setOrientation();
    }
  }
}

void Player::moveLeft(Ogre::Real deltaT)
{
  if (_position.x > -15)
  {
    _position += Ogre::Vector3(-0.5 * deltaT, 0, 0);
    _node->setPosition( _position );

    if ( _roll < MAX_ROLL)
    {
      _roll += TURN_DEGREE * deltaT;
      setOrientation();
    }
  }
}

void Player::moveToInitialState(Ogre::Real deltaT)
{
  if (_roll != 0)
  {
    if (_roll < 0)
    {
      _roll += TURN_DEGREE * deltaT;
    }
    if (_roll > 0)
    {
      _roll -= TURN_DEGREE * deltaT;
    }
  }

  if (_pitch != 0)
  {
    if (_pitch < 0)
    {
      _pitch += TURN_DEGREE * deltaT;
    }
    if (_pitch > 0)
    {
      _pitch -= TURN_DEGREE * deltaT;
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

void Player::receiveShoot()
{
  _lifes--;
  SoundFXManager::getSingletonPtr()->load("player_hurt.wav")->play();
}

int Player::getLifes()
{
  return _lifes;
}
