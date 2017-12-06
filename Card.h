#pragma once
#include<string>

class Card {

private:

	char rank;
	char suit;
	std::string fullCard;
	unsigned int strength;

public:
	
	Card(std::string card);
	std::string toString();
	char getRank() const;
	char getSuit();
	const unsigned int getStrength() const;
};