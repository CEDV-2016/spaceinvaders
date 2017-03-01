#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

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
  movePlayer();

  updateEnemies();
  updateShoots();
  checkCollitions();

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
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE || e.key == OIS::KC_P) pushState(PauseState::getSingletonPtr());
  if (e.key == OIS::KC_O) endGame(true, "Test", "150");

  if (e.key == OIS::KC_W) _moveUp = false;
  if (e.key == OIS::KC_S) _moveDown = false;
  if (e.key == OIS::KC_A) _moveLeft = false;
  if (e.key == OIS::KC_D) _moveRight = false;

  if (e.key == OIS::KC_SPACE) {
    Ogre::SceneNode* node_spaceship = _sceneMgr->getSceneNode("Spaceship");
    Ogre::Vector3 position = node_spaceship->getPosition();
    addPlayerShoot(position);
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

void PlayState::createGUI()
{
  /* code */
}

void PlayState::setPlayerName(std::string name)
{
}

void PlayState::addPlayerShoot(Ogre::Vector3 position)
{
  Shoot shoot(PLAYER_SHOOT, position, _sceneMgr);
  _player_shoots.push_back(shoot);
}

void PlayState::addEnemyShoot(Ogre::Vector3 position)
{
  Shoot shoot(ENEMY_SHOOT, position, _sceneMgr);
  _enemy_shoots.push_back(shoot);
}

void PlayState::updateEnemies()
{
  Ogre::Vector3 position;
  for (std::size_t i = 0; i < _enemies.size(); i++) {
    _enemies[i].updatePosition();

    if (_enemies[i].shoot())
    {
      position = _enemies[i].getPosition();
      addEnemyShoot(position);
    }
  }
}

void PlayState::updateShoots()
{
  for (std::size_t i = 0; i < _player_shoots.size(); i++) {
    _player_shoots[i].updatePosition();
  }

  for (std::size_t i = 0; i < _enemy_shoots.size(); i++) {
    _enemy_shoots[i].updatePosition();
  }
}

void PlayState::checkCollitions()
{

}

void PlayState::createGreenShootMaterial()
{
  Ogre::MaterialPtr mPtr = Ogre::MaterialManager::getSingleton().create
  ("green_shoot", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
  mPtr->setAmbient(Ogre::ColourValue(0.2, 0.6, 0.2)); //green
  mPtr.getPointer()->getTechnique(0)->getPass(0)->setDiffuse(0.4, 0.4, 0.4, 0);
  mPtr.getPointer()->getTechnique(0)->getPass(0)->setSpecular(0.4, 0.4, 0.4, 0);
}

void PlayState::movePlayer()
{
  Ogre::SceneNode* node_spaceship = _sceneMgr->getSceneNode("Spaceship");

  if (_moveUp)    node_spaceship->translate(0, 0, -0.05);
  if (_moveDown)  node_spaceship->translate(0, 0, 0.05);
  if (_moveLeft)  node_spaceship->translate(-0.05, 0, 0);
  if (_moveRight) node_spaceship->translate(0.05, 0, 0);
}

void PlayState::endGame(bool win, std::string name, std::string points){
  EndState* endState = EndState::getSingletonPtr();
  endState->setData(true, "Test", "150");//game->getPlayerName(), std::to_string(_game->getPoints()));
  pushState(endState);
}
