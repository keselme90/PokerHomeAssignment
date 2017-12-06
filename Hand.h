#ifndef HAND_H
#define HAND_H

#include <vector>
#include <iostream>
#include "Card.h"
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
	const Card getCard(int index) const;

};

#endif