#include "IntroState.hpp"
#include "NewGameState.hpp"
#include "PlayState.hpp"
#include "CreditsState.hpp"
#include "RankingState.hpp"

template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

void
IntroState::enter ()
{

}

void
IntroState::exit()
{

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
IntroState::frameStarted
(const Ogre::FrameEvent& evt)
{
  if(_exitGame) return false;
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

}

void
IntroState::mouseMoved
(const OIS::MouseEvent &e)
{
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

}
