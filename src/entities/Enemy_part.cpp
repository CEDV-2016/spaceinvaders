#include "Enemy_part.h"

Enemy_part::Enemy_part(Ogre::SceneManager * sceneMgr, Ogre::Vector3 init_position)
{
  _sceneMgr = sceneMgr;
  _position1 = init_position;
  _position2 = init_position;
  _position3 = init_position;


  Ogre::Entity * entity1 = _sceneMgr->createEntity("Enemy_part1.mesh");
  entity1->setCastShadows(true);
  _node1 = _sceneMgr->createSceneNode();
  _node1->attachObject(entity1);
  _node1->setPosition(_position1);
  _sceneMgr->getRootSceneNode()->addChild(_node1);

  Ogre::Entity * entity2 = _sceneMgr->createEntity("Enemy_part2.mesh");
  entity2->setCastShadows(true);
  _node2 = _sceneMgr->createSceneNode();
  _node2->attachObject(entity2);
  _node2->setPosition(_position2);
  _sceneMgr->getRootSceneNode()->addChild(_node2);

  Ogre::Entity * entity3 = _sceneMgr->createEntity("Enemy_part3.mesh");
  entity3->setCastShadows(true);
  _node3 = _sceneMgr->createSceneNode();
  _node3->attachObject(entity3);
  _node3->setPosition(_position3);
  _sceneMgr->getRootSceneNode()->addChild(_node3);
}

Enemy_part::~Enemy_part() {}

void Enemy_part::destroy()
{
  _sceneMgr->destroySceneNode(_node1);
  _sceneMgr->destroySceneNode(_node2);
  _sceneMgr->destroySceneNode(_node3);
}

bool Enemy_part::updatePosition(Ogre::Real deltaT)
{
  _position1 += Ogre::Vector3(-0.225, -0.04, 0.15) * deltaT;
  _position2 += Ogre::Vector3(-0.075, -0.04, 0.125) * deltaT;
  _position3 += Ogre::Vector3(0.125,  -0.04, 0.075) * deltaT;

  _node1->setPosition( _position1 );
  _node2->setPosition( _position2 );
  _node3->setPosition( _position3 );

  // updateRotation(deltaT);

  if (_position1.y > -2)
  {
    return true;
  }
  else{
    destroy();
    return false;
  }
}

// such a buggy method
void Enemy_part::updateRotation(Ogre::Real deltaT)
{
  double deltaR = 0.2 * deltaT;
  _pitch1 += deltaR;
  _pitch2 += deltaR;
  _pitch3 += deltaR;
  _yaw1   += deltaR;
  _yaw2   += deltaR;
  _yaw3   += deltaR;
  _roll1  += deltaR;
  _roll2  += deltaR;
  _roll3  += deltaR;

  _node1->setOrientation(Ogre::Quaternion( Ogre::Degree(_pitch1), Ogre::Vector3::UNIT_X) *
                         Ogre::Quaternion( Ogre::Degree(_yaw1),    Ogre::Vector3::UNIT_Y) *
                         Ogre::Quaternion( Ogre::Degree(_roll1),   Ogre::Vector3::UNIT_Z) );

  _node2->setOrientation(Ogre::Quaternion( Ogre::Degree(_pitch2), Ogre::Vector3::UNIT_X) *
                         Ogre::Quaternion( Ogre::Degree(_yaw2),   Ogre::Vector3::UNIT_Y) *
                         Ogre::Quaternion( Ogre::Degree(_roll2),  Ogre::Vector3::UNIT_Z) );

  _node3->setOrientation(Ogre::Quaternion( Ogre::Degree(_pitch3), Ogre::Vector3::UNIT_X) *
                         Ogre::Quaternion( Ogre::Degree(_yaw3),   Ogre::Vector3::UNIT_Y) *
                         Ogre::Quaternion( Ogre::Degree(_roll3),  Ogre::Vector3::UNIT_Z) );

}
