#pragma once
#include<string>

class Card {

private:

	char rank;
	char suit;
	std::string fullCard;

public:
	
	Card(std::string card);
	std::string toString();
	char getRank() const;
	char getSuit();
};