#pragma once

#include <Ogre.h>

#define ROTATION 0.6
class Enemy_part
{
public:
  Enemy_part(Ogre::SceneManager * sceneMgr, Ogre::Vector3 init_position);
  ~Enemy_part();
  bool updatePosition(Ogre::Real deltaT);

private:
  Ogre::Vector3 _position1, _position2, _position3;

  Ogre::SceneNode * _node1, * _node2, * _node3;

  Ogre::SceneManager * _sceneMgr;
  double getRandomDouble();
  void updateRotation(Ogre::Real deltaT);
  void destroy();

  double _roll1=0, _pitch1=0, _yaw1=0,
         _roll2=0, _pitch2=0, _yaw2=0,
         _roll3=0, _pitch3=0, _yaw3=0;
};
