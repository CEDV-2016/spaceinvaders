#include "NewGameState.h"
#include "PlayState.h"

template<> NewGameState* Ogre::Singleton<NewGameState>::msSingleton = 0;

NewGameState::NewGameState() {
  _newgameGUI = NULL;
  _nameText = NULL;
}

void
NewGameState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneManager = _root->getSceneManager("SceneManager");
  _camera = _sceneManager->getCamera("MainCamera");
  createGUI();

  _exitGame = false;
}

void
NewGameState::exit ()
{
  _newgameGUI->hide();
}

void
NewGameState::pause ()
{
}

void
NewGameState::resume ()
{
}

bool
NewGameState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
NewGameState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;

  return true;
}

void
NewGameState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
NewGameState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
NewGameState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
NewGameState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
NewGameState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

NewGameState*
NewGameState::getSingletonPtr ()
{
return msSingleton;
}

NewGameState&
NewGameState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void NewGameState::createGUI(){
    if(_newgameGUI == NULL){
    //Config Window
    _newgameGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("newGame.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_newgameGUI);

    //Config Buttons
    CEGUI::Window* newGameButton = _newgameGUI->getChild("PlayButton");
    newGameButton->subscribeEvent(CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&NewGameState::newGame, this));
    CEGUI::Window* backButton = _newgameGUI->getChild("BackButton");
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&NewGameState::back, this));
    _nameText = _newgameGUI->getChild("NameEditBox");
  } else{
    _nameText->setText("");
    _newgameGUI->show();
  }
}

bool NewGameState::newGame(const CEGUI::EventArgs &e)
{
  //PlayState* playState = PlayState::getSingletonPtr();
  //playState->setName(_nameText->getText().c_str());
  //changeState(playState);
  return true;
}

bool NewGameState::back(const CEGUI::EventArgs &e)
{
  popState();
  return true;
}
