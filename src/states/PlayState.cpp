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
  _player_shoots.clear();
  _enemy_shoots.clear();

  createGreenShootMaterial();
}

void
PlayState::exit ()
{
  _playGUI->hide();
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
  _enemies.clear();
}

void
PlayState::pause()
{
}

void
PlayState::resume()
{
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

  updateEnemies();
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
  if (e.key == OIS::KC_P) pushState(PauseState::getSingletonPtr());

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

  // Creating 3 enemies
  for (int i = 0; i < 3; i++) {
    Enemy aux(_sceneMgr);
    _enemies.push_back(aux);
  }
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

  _player_shoots.push_back(node_shoot);
}

void PlayState::addEnemyShoot(int x, int z)
{
  Ogre::Entity* ent_shoot = _sceneMgr->createEntity("Shoot.mesh");
  ent_shoot->getSubEntity(0)->setMaterialName("green_shoot");
  Ogre::SceneNode* node_shoot = _sceneMgr->createSceneNode();
  node_shoot->attachObject(ent_shoot);
  node_shoot->setPosition(x+0.05, 0, z);
  _sceneMgr->getRootSceneNode()->addChild(node_shoot);

  _enemy_shoots.push_back(node_shoot);
}

void PlayState::updateEnemies()
{
  Ogre::Vector3 aux_vector;
  for (std::size_t i = 0; i < _enemies.size(); i++) {
    _enemies[i].updatePosition();

    if (_enemies[i].shoot())
    {
        aux_vector = _enemies[i].getPosition();
        addEnemyShoot(aux_vector.x, aux_vector.z);
    }
  }
}

void PlayState::updateShoots()
{

  Ogre::SceneNode* aux_node;
  Ogre::Vector3 aux_vector;
  std::size_t i;
  for (i = 0; i < _player_shoots.size(); i++) {
    aux_node = _player_shoots[i];
    aux_vector = aux_node->getPosition();

    if (aux_vector.z < -30) {
      // _sceneMgr->destroySceneNode(aux_node);
      // _player_shoots.remove(aux_node);
    }
    else {
      aux_node->translate(0, 0, -0.03);
    }
  }

  for (i = 0; i < _enemy_shoots.size(); i++) {
    aux_node = _enemy_shoots[i];
    aux_vector = aux_node->getPosition();

    if (aux_vector.z > 30) {
      // _sceneMgr->destroySceneNode(aux_node);
      // _enemy_shoots.remove(aux_node);
    }
    else {
      aux_node->translate(0, 0, 0.035);
    }
  }
}

void PlayState::createGreenShootMaterial() {
  Ogre::MaterialPtr mPtr = Ogre::MaterialManager::getSingleton().create
  ("green_shoot", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
  mPtr->setAmbient(Ogre::ColourValue(0.2, 0.6, 0.2));
  mPtr.getPointer()->getTechnique(0)->getPass(0)->setDiffuse(0.4, 0.4, 0.4, 0);
  mPtr.getPointer()->getTechnique(0)->getPass(0)->setSpecular(0.4, 0.4, 0.4, 0);
}
