#include "NewGameState.hpp"
#include "PlayState.hpp"
#include "SoundFXManager.hpp"

template<> NewGameState* Ogre::Singleton<NewGameState>::msSingleton = 0;

NewGameState::NewGameState() {
  _newgame = NULL;
  _nameText = NULL;
}

void
NewGameState::enter ()
{

}

void
NewGameState::exit ()
{
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

}
