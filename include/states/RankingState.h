#ifndef RankingState_H
#define RankingState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

#include "GameState.h"
#include "RankingManager.h"

class RankingState : public Ogre::Singleton<RankingState>, public GameState
{
public:
  RankingState();

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
  static RankingState& getSingleton ();
  static RankingState* getSingletonPtr ();

  void createGUI();

  bool back(const CEGUI::EventArgs &e);

  Ogre::Root* _root;
protected:
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  Ogre::SceneManager* _sceneMgr;
  Ogre::RaySceneQuery *_raySceneQuery;
  Ogre::SceneNode *_selectedNode;
  CEGUI::OgreRenderer* renderer;
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  CEGUI::Window* _rankingGUI;
  RankingManager* _rankingManager;

  bool _exitGame;
};

#endif
