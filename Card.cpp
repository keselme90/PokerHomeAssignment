#include "Card.h"

Card::Card(std::string card) {

	fullCard = card;
	rank = card[0];
	suit = card[1];
	if (rank == 'A')
		strength = 14;
	else
		strength = CardMapping::mymap[rank];
}

std::string Card::toString() {

	return fullCard;
}

const char Card::getRank() const
{
	return rank;
}

 const char Card::getSuit() const
{
	return suit;
}

 const unsigned int Card::getStrength() const {

	 return strength;
 }
