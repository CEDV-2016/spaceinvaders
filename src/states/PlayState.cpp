#include "PlayState.hpp"
#include "PauseState.hpp"
#include "GameManager.hpp"
#include "GameOverState.hpp"
#include "SoundFX.hpp"
#include "SoundFXManager.hpp"

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

PlayState::PlayState() {
  _game = new Game();
}

void
PlayState::enter ()
{

}

void
PlayState::exit ()
{

}

void
PlayState::pause()
{
  _gameGUI->hide();
}

void
PlayState::resume()
{
  _gameGUI->show();
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{
  return !_exitGame;
}

void
PlayState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{

}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
  _mouse_x = e.state.X.abs;
  _mouse_y = e.state.Y.abs;
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  _left_click = true;
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PlayState*
PlayState::getSingletonPtr ()
{
  return msSingleton;
}

PlayState&
PlayState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void PlayState::createScene() {

}

void PlayState::createGUI()
{

}
