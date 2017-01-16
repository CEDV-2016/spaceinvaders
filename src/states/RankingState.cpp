#include <sstream>

#include "RankingState.hpp"
#include "SoundFXManager.hpp"

template<> RankingState* Ogre::Singleton<RankingState>::msSingleton = 0;

RankingState::RankingState() {
  _ranking = NULL;
  _rankingManager = new RankingManager;
}

void
RankingState::enter ()
{

}

void
RankingState::exit ()
{

}

void
RankingState::pause ()
{
}

void
RankingState::resume ()
{
}

bool
RankingState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
RankingState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;

  return true;
}

void
RankingState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
RankingState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
RankingState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
RankingState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
RankingState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

RankingState*
RankingState::getSingletonPtr ()
{
return msSingleton;
}

RankingState&
RankingState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void RankingState::createGUI(){

}
