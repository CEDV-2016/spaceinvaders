#include "RankingManager.hpp"

std::vector<std::string> RankingManager::getRanking () {
  if (_rankings.size() == 0) {
    this->loadRankings();
  }
  return _rankings;
}

bool RankingManager::checkRanking (int turns) {
  return false;
}

void RankingManager::setRanking (std::string name, int turns) {

}

void RankingManager::saveRankings () {

}

void RankingManager::loadRankings () {

}
