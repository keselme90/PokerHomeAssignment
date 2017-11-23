#include "Card.h"
#include <string>

Card::Card(std::string card) {

	fullCard = card;
	rank = card[0];
	suit = card[1];
}

std::string Card::toString() {

	return fullCard;
}

 char Card::getRank() const
{
	return rank;
}

 char Card::getSuit() 
{
	return suit;
}
