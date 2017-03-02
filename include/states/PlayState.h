#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include <iostream>
#include <string>
#include <vector>

#include "GameState.h"
#include "Enemy.h"
#include "Shoot.h"

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

  // Heredados de Ogre::Singleton.
  static PlayState& getSingleton ();
  static PlayState* getSingletonPtr ();

  void createScene();
  void createGUI();

  void setPlayerName(std::string name);

  void movePlayer();
  void addPlayerShoot(Ogre::Vector3 position);
  void addEnemyShoot(Ogre::Vector3 position);
  void updateEnemies();
  void updateShoots();
  void checkCollitions();
  void checkPlayerCollitions();
  void checkEnemiesCollitions();
  void endGame(bool win, std::string name, std::string points);

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
  CEGUI::Window* _playGUI;

  bool _exitGame;
  bool _evenFrame;

  bool _moveRight, _moveLeft, _moveUp, _moveDown;
  std::vector<Shoot> _player_shoots, _enemy_shoots;
  std::vector<Enemy> _enemies;
};

#endif
