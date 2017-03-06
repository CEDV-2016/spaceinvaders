#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

PlayState::PlayState()
{
  _game = new Game();
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
  _game->restart();
  _scoreView->setText("Score: " + std::to_string(_game->getPoints()));
}

void
PlayState::exit ()
{
  _playGUI->hide();
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
  _enemies.clear();
  _enemy_shoots.clear();
  _player_shoots.clear();
  _enemy_parts.clear();
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
  Ogre::Real deltaT = evt.timeSinceLastFrame;
  deltaT *= 25.0;
  // Moves the player basing on the pressed keys
  movePlayer(deltaT);

  // Updates the enemies' position and makes them shoot
  updateEnemies(deltaT);

  // Updates the position of all shoots
  updateShoots(deltaT);

  // Checks whether a collition between spaceships and shoots has occurred
  checkCollitions(deltaT);

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

  if (e.key == OIS::KC_W) _moveUp = false;
  if (e.key == OIS::KC_S) _moveDown = false;
  if (e.key == OIS::KC_A) _moveLeft = false;
  if (e.key == OIS::KC_D) _moveRight = false;

  if (e.key == OIS::KC_SPACE) addPlayerShoot( _player.getPosition() );
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

void PlayState::createScene()
{
  // Creating light
  Ogre::Light *light = _sceneMgr->createLight("MainLight");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDirection(Ogre::Vector3(0, -1, 0));

  // Creating the ground
  Ogre::Plane plane1(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("plane1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
  plane1, 200, 200, 1, 1, true, 1, 20, 20, Ogre::Vector3::UNIT_Z);
  Ogre::Entity* ground_ent = _sceneMgr->createEntity("planeEnt", "plane1");
  ground_ent->setMaterialName("Sea.material");
  Ogre::SceneNode* node_ground = _sceneMgr->createSceneNode("ground");
  node_ground->attachObject(ground_ent);
  _sceneMgr->getRootSceneNode()->addChild(node_ground);

  // Creating the spaceship
  if (_game->getPlayerName() == "CEDV" || _game->getPlayerName() == "cedv") // an small easter egg :P
  {
    _player.create("Blue", _sceneMgr);
  }
  else
  {
    _player.create("Red", _sceneMgr);
  }

  // Creating several enemies
  for (int i = 0; i < Game::INITIAL_ENEMIES; i++)
  {
    createEnemy();
  }
}

void PlayState::createGUI()
{
  if(_playGUI == NULL){
    //Config Window
    _playGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("play.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_playGUI);

    //Config Buttons
    CEGUI::Window* _layout = _playGUI->getChild("FrameWindow");
    _nameView = _layout->getChild("NameLabel");
    _scoreView = _layout->getChild("ScoreLabel");
    _life1View = _layout->getChild("Live1");
    _life2View = _layout->getChild("Live2");
    _life3View = _layout->getChild("Live3");

    //Set values
    _nameView->setText(_game->getPlayerName());
  } else
  {
    _nameView->setText(_game->getPlayerName());
    _playGUI->show();
  }
}

void PlayState::updateGUI() {
  switch (_player.getLifes()) {
    case 2:
    _life3View->setVisible(false);
    break;
    case 1:
    _life2View->setVisible(false);
    break;
    case 0:
    _life1View->setVisible(false);
    break;
  }
}

void PlayState::setPlayerName(std::string name)
{
  _game->setPlayerName(name);
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

void PlayState::updateEnemies(Ogre::Real deltaT)
{
  Ogre::Vector3 position;
  for (std::size_t i = 0; i < _enemies.size(); i++)
  {
    _enemies[i].updatePosition(deltaT);

    if (_enemies[i].shoot())
    {
      position = _enemies[i].getPosition();
      addEnemyShoot(position);
    }
  }

  if (_phase == BOSS)
  {
    bool continue_playing;
    continue_playing = _boss.updatePosition(deltaT);
    
    if ( !continue_playing )
    {
      for (int i = 0; i < 5; i++) _game->destroyEnemy(); //givin more points to player
      _scoreView->setText("Score: " + std::to_string(_game->getPoints()));
      endGame(true);
    }
    else
    {
      if (_boss.shoot()) //one shoot per cannon
      {
        position = _boss.getPosition();
        position += Ogre::Vector3(2.2, 0, 1.5);
        addEnemyShoot(position);

        position = _boss.getPosition();
        position -= Ogre::Vector3(2.2, 0, 1.5);
        addEnemyShoot(position);
      }
    }
  }
}

void PlayState::updateShoots(Ogre::Real deltaT)
{
  bool valid;
  for (std::size_t i = 0; i < _player_shoots.size(); i++)
  {
    valid = _player_shoots[i].updatePosition(deltaT);

    if (!valid) // if it goes out of the screen will be deleted
    {
      _player_shoots.erase(_player_shoots.begin() + i);
      i--;
    }
  }

  for (std::size_t i = 0; i < _enemy_shoots.size(); i++)
  {
    valid = _enemy_shoots[i].updatePosition(deltaT);

    if (!valid)
    {
      _enemy_shoots.erase(_enemy_shoots.begin() + i);
      i--;
    }
  }
}

// On even frames checking player collitions and on odd ones enemies collitions
void PlayState::checkCollitions(Ogre::Real deltaT)
{
  _evenFrame = !_evenFrame;

  if (_evenFrame)
  {
    checkPlayerCollitions(deltaT);
  }
  else
  {
    checkEnemiesCollitions(deltaT);
  }
}

void PlayState::checkPlayerCollitions(Ogre::Real deltaT)
{
  Ogre::SceneNode* node_spaceship = _player.getSceneNode();
  bool collition;

  for (std::size_t i = 0; i < _enemy_shoots.size(); i++) //for each enemy shoot
  {
    collition = _enemy_shoots[i].checkCollition(node_spaceship);

    if (collition)
    {
      // Deleting that shoot from its vector and decreasing players' health
      _enemy_shoots.erase(_enemy_shoots.begin() + i);
      i--;
      _player.receiveShoot();

      std::cout << "COLLITION DETECTED (player & enemy shoot). " << _player.getLifes() << " lifes remaining\n";
      updateGUI();

      if (_player.getLifes() <= 0)
      {
        endGame(false);
      }
    }
  }
}

void PlayState::checkEnemiesCollitions(Ogre::Real deltaT)
{
  bool collition;

  if (_phase == ENEMIES)
  {
    for (std::size_t i = 0; i < _player_shoots.size(); i++)  //for each player shoot
    {
      for (std::size_t j = 0; j < _enemies.size(); j++)  //for each enemy
      {
        collition = _player_shoots[i].checkCollition(_enemies[j].getSceneNode());

        if (collition) // deleting shoot and enemy
        {
          // std::cout << "COLLITION DETECTED (enemy & player shoot)" << "\n";

          Enemy_part parts(_sceneMgr, _enemies[j].getPosition());
          _enemy_parts.push_back(parts);

          // Delete the destroyed enemy from the scene manager and from the game
          _enemies[j].destroy();
          _game->destroyEnemy();
          _scoreView->setText("Score: " + std::to_string(_game->getPoints()));

          // Delete shoot and enemy from its respective vectors
          _player_shoots.erase(_player_shoots.begin() + i);
          i--;
          _enemies.erase(_enemies.begin() + j);
          j--;

          // Keep playing if there are enemies left
          if ( _game->enemiesLeft() )
          {
            createEnemy();
          }
          else if ( _enemies.size() == 0 ) // If every enemy has been destroyed
          {
            // Oh! The boss appeared
            _boss.create(_sceneMgr);
            _phase = BOSS;
          }
        }
      }
    }
  }
  else if (_phase == BOSS)
  {
    for (std::size_t i = 0; i < _player_shoots.size(); i++)  //for each player shoot
    {
      collition = _player_shoots[i].checkCollition( _boss.getSceneNode());

      if (collition)
      {
        _boss.receiveShoot();
      }
    }
  }
  updateEnemyParts(deltaT);
}

void PlayState::updateEnemyParts(Ogre::Real deltaT)
{
  bool valid;
  for (std::size_t i = 0; i < _enemy_parts.size(); i++)  //for each enemy part
  {
    valid = _enemy_parts[i].updatePosition(deltaT);

    if ( !valid ) //if is below the ground
    {
      _enemy_parts.erase( _enemy_parts.begin() + i );
      i--;
    }
  }
}

void PlayState::movePlayer(Ogre::Real deltaT)
{
  if (_moveUp)    _player.moveForward(deltaT);
  if (_moveDown)  _player.moveBackward(deltaT);
  if (_moveLeft)  _player.moveLeft(deltaT);
  if (_moveRight) _player.moveRight(deltaT);
  if (!_moveUp && !_moveRight && !_moveLeft && !_moveRight) _player.moveToInitialState(deltaT);
}

void PlayState::createEnemy()
{
  Enemy aux(_sceneMgr);
  _enemies.push_back(aux);
  _game->createEnemy();
}

void PlayState::endGame(bool win){
  _phase = ENEMIES;
  EndState* endState = EndState::getSingletonPtr();
  endState->setData(win, _game->getPlayerName(), _game->getPoints());
  pushState(endState);
}
