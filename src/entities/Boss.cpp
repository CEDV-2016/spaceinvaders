#include "Boss.h"
#include "SoundFXManager.h"

Boss::Boss() {}

Boss::~Boss() {}

void Boss::create(Ogre::SceneManager* sceneMgr)
{
  _position = Ogre::Vector3 ( 0, 0, -25 );
  _roll = 0;
  _sceneMgr = sceneMgr;
  _move_towards = MOVE_LEFT;
  _lifes = BOSS_LIFE;
  _state = APPEARING;

  Ogre::Entity * entity = _sceneMgr->createEntity("Boss.mesh");
  entity->setCastShadows(true);
  _node = _sceneMgr->createSceneNode("Boss");
  _node->attachObject(entity);
  _node->scale(Ogre::Vector3(1.2, 1.2, 1.2));
  _node->setPosition(_position);
  _sceneMgr->getRootSceneNode()->addChild(_node);

  SoundFXManager::getSingletonPtr()->load("mechanic_groan.wav")->play();
}

bool Boss::updatePosition(Ogre::Real deltaT)
{
  switch ( _state )
  {
    case APPEARING:
      if (_position.z < -6 ) //move to aprox. half of the screen
      {
        _position += Ogre::Vector3(0, 0, 0.15 * deltaT);
      }
      else
      {
        _state = MOVING;
      }
    break;

    case MOVING:
      if(_move_towards == MOVE_LEFT)
      {
        if (_position.x > -10)
        {
          _position += Ogre::Vector3(-0.15 * deltaT, 0, 0);

          if (_roll < MAX_ROLL_BOSS) _roll += TURN_DEGREE_BOSS * deltaT;
        }
        else // the boss has reached left limit move right
        {
          _move_towards = MOVE_RIGHT;
        }
      }
      else if (_move_towards == MOVE_RIGHT)
      {
        if (_position.x < 10)
        {
          _position += Ogre::Vector3(0.01, 0, 0);

          if (_roll > -MAX_ROLL_BOSS) _roll -= TURN_DEGREE_BOSS * deltaT;
        }
        else //the boss has reached the right limit of the screen
        {
          _move_towards = MOVE_LEFT;
        }
      }
    break;

    case DYING:
      if (_position.y > -4)
      {
        _position += Ogre::Vector3(0, -0.03 * deltaT, 0); //slowly going down

        if (_roll != 0)
        {
          if ( _roll > 0)     _roll -= TURN_DEGREE_BOSS * deltaT;
          else if (_roll < 0) _roll += TURN_DEGREE_BOSS * deltaT;
        }
      }
      else //the boss has reached the bottom of the ground
      {
        return false; // when boss::updateposition return false the game is over
      }
    break;
  }

  setOrientation();
  _node->setPosition(_position);
  return true;
}
bool Boss::shoot()
{
  if ( _state == DYING ) return false;

  int min = 0, max = 1000, probability = 3;

  int randNum = rand()%(max-min + 1) + min;

  return randNum <= probability;
}

void Boss::receiveShoot()
{
  _lifes--;

  if( _lifes <= 0)
  {
    _state = DYING;
    SoundFXManager::getSingletonPtr()->load("mechanic_sink.wav")->play();
  }
}

Ogre::Vector3 Boss::getPosition()
{
  return _position;
}

Ogre::SceneNode * Boss::getSceneNode()
{
  return _node;
}

void Boss::setOrientation()
{
  _node->setOrientation(Ogre::Quaternion( Ogre::Degree(0),     Ogre::Vector3::UNIT_X) *
                        Ogre::Quaternion( Ogre::Degree(0),     Ogre::Vector3::UNIT_Y) *
                        Ogre::Quaternion( Ogre::Degree(_roll), Ogre::Vector3::UNIT_Z) );
}
