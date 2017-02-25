#include "PlayState.h"
#include "PauseState.h"
#include <iostream>

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

PlayState::PlayState(){
  _playGUI = NULL;
}

void
PlayState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  createScene();
  createGUI();

  _exitGame = false;
  _moveUp = _moveDown = _moveRight = _moveLeft = false;
  _shoots.clear();
}

void
PlayState::exit ()
{
  _playGUI->hide();
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
PlayState::pause()
{
  _playGUI->show();
}

void
PlayState::resume()
{
  _playGUI->show();
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  Ogre::SceneNode* node_spaceship = _sceneMgr->getSceneNode("Spaceship");

  if (_moveUp) node_spaceship->translate(0, 0, -0.05);
  if (_moveDown) node_spaceship->translate(0, 0, 0.05);
  if (_moveLeft) node_spaceship->translate(-0.05, 0, 0);
  if (_moveRight) node_spaceship->translate(0.05, 0, 0);

  updateShoots();
  return true;
}

bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
PlayState::keyPressed
(const OIS::KeyEvent &e)
{

  if (e.key == OIS::KC_W) _moveUp = true;
  if (e.key == OIS::KC_S) _moveDown = true;
  if (e.key == OIS::KC_A) _moveLeft = true;
  if (e.key == OIS::KC_D) _moveRight = true;

  Ogre::Vector3 vt(0,0,0);
  Ogre::Real tSpeed = 20.0;
  if(e.key ==  OIS::KC_UP)   vt+=Ogre::Vector3(0,0,-1);
  if(e.key == OIS::KC_DOWN)  vt+=Ogre::Vector3(0,0,1);
  if(e.key == OIS::KC_LEFT)  vt+=Ogre::Vector3(-1,0,0);
  if(e.key == OIS::KC_RIGHT) vt+=Ogre::Vector3(1,0,0);
  _camera->moveRelative(vt * tSpeed);

}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) _exitGame = true;

  if (e.key == OIS::KC_W) _moveUp = false;
  if (e.key == OIS::KC_S) _moveDown = false;
  if (e.key == OIS::KC_A) _moveLeft = false;
  if (e.key == OIS::KC_D) _moveRight = false;

  if (e.key == OIS::KC_SPACE) {
    Ogre::SceneNode* node_spaceship = _sceneMgr->getSceneNode("Spaceship");
    Ogre::Vector3 aux_vector = node_spaceship->getPosition();

    addPlayerShoot(aux_vector.x, aux_vector.z);
  }

}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PlayState*
PlayState::getSingletonPtr ()
{
  return msSingleton;
}

PlayState&
PlayState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void PlayState::createScene() {
  // Creating the spaceship
  Ogre::Entity* ent_spaceship = _sceneMgr->createEntity("Spaceship", "Spaceship.mesh");
  Ogre::SceneNode* node_spaceship = _sceneMgr->createSceneNode("Spaceship");
  node_spaceship->attachObject(ent_spaceship);
  node_spaceship->setPosition(0, 0, 5);
  _sceneMgr->getRootSceneNode()->addChild(node_spaceship);

  // Creating two enemy
  Ogre::Entity* ent_enemy1 = _sceneMgr->createEntity("Enemy1", "Enemy.mesh");
  Ogre::SceneNode* node_enemy1 = _sceneMgr->createSceneNode("Enemy1");
  node_enemy1->attachObject(ent_enemy1);
  node_enemy1->setPosition(4, 0, -5);
  _sceneMgr->getRootSceneNode()->addChild(node_enemy1);

  Ogre::Entity* ent_enemy2 = _sceneMgr->createEntity("Enemy2", "Enemy.mesh");
  Ogre::SceneNode* node_enemy2 = _sceneMgr->createSceneNode("Enemy2");
  node_enemy2->attachObject(ent_enemy2);
  node_enemy2->setPosition(-4, 0, -5);
  _sceneMgr->getRootSceneNode()->addChild(node_enemy2);
}

void PlayState::createGUI() {
  /* code */
}

void PlayState::setName(std::string name)
{
}

void PlayState::addPlayerShoot(int x, int z)
{
  Ogre::Entity* ent_shoot = _sceneMgr->createEntity("Shoot.mesh");
  Ogre::SceneNode* node_shoot = _sceneMgr->createSceneNode();
  node_shoot->attachObject(ent_shoot);
  node_shoot->setPosition(x+0.05, 0, z);
  _sceneMgr->getRootSceneNode()->addChild(node_shoot);

  _shoots.push_back(node_shoot);
}

void PlayState::updateShoots()
{

  Ogre::SceneNode* aux_node;
  Ogre::Vector3 aux_vector;
  std::size_t i;
  for (i = 0; i < _shoots.size(); i++) {
    aux_node = _shoots[i];
    aux_vector = aux_node->getPosition();

    if (aux_vector.z < -30)
    {
      // _sceneMgr->destroySceneNode(aux_node);
      // _shoots.remove(aux_node);
    }
    else
    {
      aux_node->translate(0, 0, -0.03);
    }
  }
}
