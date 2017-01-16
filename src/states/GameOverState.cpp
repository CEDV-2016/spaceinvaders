#include "IntroState.hpp"
#include "PlayState.hpp"
#include "GameOverState.hpp"

template<> GameOverState* Ogre::Singleton<GameOverState>::msSingleton = 0;

GameOverState::GameOverState() {
  _gameover = NULL;
}

void
GameOverState::enter ()
{

}

void
GameOverState::exit ()
{
  _gameover->hide();
}

void
GameOverState::pause ()
{
  _gameover->hide();
}

void
GameOverState::resume ()
{
}

bool
GameOverState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
GameOverState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
GameOverState::keyPressed
(const OIS::KeyEvent &e) {

}

void
GameOverState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
GameOverState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
GameOverState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
GameOverState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

GameOverState*
GameOverState::getSingletonPtr ()
{
  return msSingleton;
}

GameOverState&
GameOverState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void GameOverState::createGUI()
{

}
