#include "IntroState.hpp"
#include "PauseState.hpp"

template<> PauseState* Ogre::Singleton<PauseState>::msSingleton = 0;

void
PauseState::enter ()
{

}

void
PauseState::exit ()
{
  _pause->hide();
}

void
PauseState::pause ()
{
}

void
PauseState::resume ()
{
}

bool
PauseState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
PauseState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;

  return true;
}

void
PauseState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
PauseState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_P) popState();
}

void
PauseState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
PauseState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PauseState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PauseState*
PauseState::getSingletonPtr ()
{
return msSingleton;
}

PauseState&
PauseState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void PauseState::createGUI()
{

}
