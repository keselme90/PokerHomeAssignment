#include "Card.h"
#include "CardMapping.h"
#include <string>

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

 char Card::getRank() const
{
	return rank;
}

 char Card::getSuit() 
{
	return suit;
}

 const unsigned int Card::getStrength() const {

	 return strength;
 }
