#define UNUSED_VARIABLE(x) (void)x

#include "GameManager.h"
#include "IntroState.h"
#include "MainState.h"
#include "NewGameState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "CreditsState.h"
#include "RankingState.h"
#include "EndState.h"

#include <iostream>

using namespace std;

int main () {

  GameManager* game = new GameManager();
  IntroState* introState = new IntroState();
  MainState* mainState = new MainState();
  NewGameState* newGameState = new NewGameState();
  PlayState* playState = new PlayState();
  PauseState* pauseState = new PauseState();
  CreditsState* creditsState = new CreditsState();
  RankingState* rankingState = new RankingState();
  EndState* endState = new EndState();

  UNUSED_VARIABLE(introState);
  UNUSED_VARIABLE(mainState);
  UNUSED_VARIABLE(newGameState);
  UNUSED_VARIABLE(playState);
  UNUSED_VARIABLE(pauseState);
  UNUSED_VARIABLE(creditsState);
  UNUSED_VARIABLE(rankingState);
  UNUSED_VARIABLE(endState);

  try
    {
      game->start(IntroState::getSingletonPtr());
    }
  catch (Ogre::Exception& e)
    {
      std::cerr << "Excepción detectada: " << e.getFullDescription();
    }

  delete game;

  return 0;
}
