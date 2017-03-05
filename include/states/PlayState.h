#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include <iostream>
#include <string>
#include <vector>

#include "Game.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Shoot.h"

#define ENEMIES 0
#define BOSS    1

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
public:
  PlayState ();

  void enter ();
  void exit ();
  void pause ();
  void resume ();

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);

  void mouseMoved (const OIS::MouseEvent &e);
  void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

  bool frameStarted (const Ogre::FrameEvent& evt);
  bool frameEnded (const Ogre::FrameEvent& evt);

  // Inherited from Ogre::Singleton.
  static PlayState& getSingleton ();
  static PlayState* getSingletonPtr ();

  void createScene();
  void createGUI();

  void setPlayerName(std::string name);

  void endGame(bool win);

protected:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  Ogre::RaySceneQuery *_raySceneQuery;
  Ogre::SceneNode *_selectedNode;
  CEGUI::OgreRenderer* renderer;
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  CEGUI::Window* _playGUI, *_nameView, *_scoreView, *_life1View, *_life2View, *_life3View;
  Game *_game;
  std::string _name;

  bool _exitGame;
  bool _evenFrame;

  bool _moveRight, _moveLeft, _moveUp, _moveDown;
  std::vector<Shoot> _player_shoots, _enemy_shoots;
  std::vector<Enemy> _enemies;
  Player _player;
  Boss _boss;
  std::string _player_color;
  int _phase = ENEMIES;

  void movePlayer();
  void addPlayerShoot(Ogre::Vector3 position);
  void addEnemyShoot(Ogre::Vector3 position);
  void updateEnemies();
  void updateShoots();
  void checkCollitions();
  void checkPlayerCollitions();
  void checkEnemiesCollitions();
  void createEnemy();
};

#endif
