#include "Hand.h"

/*
	Constructor
	Receives a string that represents the Cards.
	Parse the string and creates a vector of cards.
*/
Hand::Hand(std::string cards) {

	cards = cards.substr(cards.find(":") + 1);
	while (cards.size() != 2) {

		Card card(cards.substr(0, cards.find("-")));
		myCards.push_back(card);
		cards = cards.substr(cards.find("-") + 1);
	}
	Card card(cards);
	myCards.push_back(card);
}

/**
Returns a specific card from the vector according a given index.
*/
Card Hand::getCard(int index) {

	return myCards[index];
}

/**
* Prints the deck of cards to the screen
*/
void Hand::printHand(){

	std::cout << "My hand is: ";
	for (std::vector<Card>::iterator it = myCards.begin(); it != myCards.end(); it++)
		std::cout << it->toString() << " ";

	std::cout << std::endl;
}
