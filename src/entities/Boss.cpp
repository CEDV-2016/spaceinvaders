#include "Boss.h"

Boss::Boss() {}

Boss::~Boss() { }

void Boss::create(Ogre::SceneManager* sceneMgr)
{
  _position = Ogre::Vector3 ( 0, 0, -20 );
  _roll = 0;
  _sceneMgr = sceneMgr;
  _move_towards = MOVE_LEFT;
  _lifes = BOSS_LIFE;

  Ogre::Entity * entity = _sceneMgr->createEntity("Boss.mesh");
  entity->setCastShadows(true);
  _node = _sceneMgr->createSceneNode("Boss");
  _node->attachObject(entity);
  _node->scale(Ogre::Vector3(1.2, 1.2, 1.2));
  _node->setPosition(_position);
  _sceneMgr->getRootSceneNode()->addChild(_node);
}

void Boss::updatePosition(Ogre::Real deltaT)
{
  if (_position.z < -6 ) //move to ~ half of the screen
  {
    _position += Ogre::Vector3(0, 0, 0.15 * deltaT);
  }
  else
  {
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
  }
  _node->setPosition(_position);
  setOrientation();
}

bool Boss::shoot()
{
  int min = 0, max = 1000, probability = 3;

  int randNum = rand()%(max-min + 1) + min;

  return randNum <= probability;
}

void Boss::receiveShoot()
{
  _lifes--;
}

bool Boss::isAlive()
{
  return _lifes > 0;
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
