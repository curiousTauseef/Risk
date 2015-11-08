#include "player_view.h"


PlayerView::PlayerView(Player *player)
{
    this->player = player;
    update();
}

PlayerView::~PlayerView()
{
    delete this->player;
}

void PlayerView::update(){
    this->countriesOwned = player->getCountryOwned();
    this->continentsOwned = player->getContinentsOwned();
    this->nbrOfReinforcements = player->getReinforcements();
    this->nbrOfArmies = player->getTotalArmy();
    this->nbrBattleWon = player->getBattlesWon();
	this->name = player->getName();
}

std::string PlayerView::getName() const
{
    return this->name;
}

std::set<std::string> PlayerView::getCountriesOwned() const
{
	return this->countriesOwned;
}

std::set<std::string> PlayerView::getContinentsOwned() const
{
	return this->continentsOwned;
}

int PlayerView::getNumberOfReinforcements() const
{
	return this->nbrOfReinforcements;
}

int PlayerView::getNumberOfArmies() const
{
	return this->nbrOfArmies;
}

int PlayerView::getNumberOfBattleWon() const
{
	return this->nbrBattleWon;
}
