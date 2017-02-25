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
  Ogre::SceneNode* node_spaceship = _sceneMgr->getSceneNode("Spaceship");
  if (e.key == OIS::KC_W) node_spaceship->translate(0, 0, -0.5);
  if (e.key == OIS::KC_S) node_spaceship->translate(0, 0, 0.5);
  if (e.key == OIS::KC_A) node_spaceship->translate(-0.5, 0, 0);
  if (e.key == OIS::KC_D) node_spaceship->translate(0.5, 0, 0);

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
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
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
}

void PlayState::createGUI() {
  /* code */
}

void PlayState::setName(std::string name)
{
}
