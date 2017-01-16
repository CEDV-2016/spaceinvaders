#include "CreditsState.hpp"
#include "SoundFXManager.hpp"

template<> CreditsState* Ogre::Singleton<CreditsState>::msSingleton = 0;

CreditsState::CreditsState() {
  _credits = NULL;
}


void
CreditsState::enter ()
{

}

void
CreditsState::exit ()
{

}

void
CreditsState::pause ()
{
}

void
CreditsState::resume ()
{
}

bool
CreditsState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
CreditsState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
CreditsState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
CreditsState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
CreditsState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
CreditsState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
CreditsState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

CreditsState*
CreditsState::getSingletonPtr ()
{
  return msSingleton;
}

CreditsState&
CreditsState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void CreditsState::createGUI(){

}
