#ifndef CARD_H
#define CARD_H

#include<string>
#include "CardMapping.h"

class Card {

private:

	char rank;
	char suit;
	std::string fullCard;
	unsigned int strength;

public:
	
	Card(std::string card);
	std::string toString();
	const char getRank() const;
	const char getSuit() const;
	const unsigned int getStrength() const;
};

#endif