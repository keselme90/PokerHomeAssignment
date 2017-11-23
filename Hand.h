#pragma once
#include <vector>
#include "Card.h"
#include <iostream>
#include "CardMapping.h"

/**
* Class that represents the Hand of the player
*/
class Hand {

private:

	std::vector<Card> myCards;
	bool isFirstTimeUpdate;

public:

	Hand(std::string cards);
	void printHand();
	Card getCard(int index);

};