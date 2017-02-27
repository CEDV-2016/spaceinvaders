#include "IntroState.h"
#include "MainState.h"

template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

void
IntroState::enter ()
{
  if (_root == NULL) {
    _root = Ogre::Root::getSingletonPtr();
  }
  if (_sceneMgr == NULL) {
    _sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
  }
  if (_camera == NULL) {
    _camera = _sceneMgr->createCamera("MainCamera");
  }

  _viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
  _viewport->setBackgroundColour(Ogre::ColourValue(0.2, 0.4, 0.6));

  // Creating and placing camera
  _camera->setPosition(Ogre::Vector3(0, 25, 2)); //X Z -Y
  _camera->lookAt(Ogre::Vector3(0, 0, 0));
  _camera->setNearClipDistance(0.11);
  _camera->setFarClipDistance(1000);
  _camera->setFOVy(Ogre::Degree(40));
  double width = _viewport->getActualWidth();
  double height = _viewport->getActualHeight();
  _camera->setAspectRatio(width / height);

  /* And there was light! */
  _sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
  _sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

  createScene();
  createGUI();

  _exitGame = false;
}

void
IntroState::exit()
{
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
IntroState::pause ()
{
  _intro->hide();
}

void
IntroState::resume ()
{
  _intro->show();
}

bool
IntroState::frameStarted/* code */
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
IntroState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
IntroState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
IntroState::keyReleased
(const OIS::KeyEvent &e )
{
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }else if (e.key == OIS::KC_SPACE) {
    pushState(MainState::getSingletonPtr());
  }
}

void
IntroState::mouseMoved
(const OIS::MouseEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(e.state.X.abs, e.state.Y.abs);
}

void
IntroState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
IntroState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

IntroState*
IntroState::getSingletonPtr ()
{
  return msSingleton;
}

IntroState&
IntroState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void IntroState::createScene() {
}

void IntroState::createGUI()
{
  if(_intro == NULL){
    //Config Window
    _intro = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("splash.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_intro);
  } else{
    _intro->show();
  }
}
