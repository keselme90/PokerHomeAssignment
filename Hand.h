#pragma once
#include <vector>
#include "Card.h"
#include <iostream>
#include <algorithm>
#include "CardMapping.h"

class Hand {

private:

	std::vector<Card> myCards;
	int lowestValue;

public:

	Hand(std::string cards);
	void sortLowToHigh();
	void printHand();
	friend bool lowToHighComparison(Card a, Card b);
	const int getLowestValue() const;
	Card getCard(int index);
};