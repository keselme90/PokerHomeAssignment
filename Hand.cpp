#include "Hand.h"


Hand::Hand(std::string cards) {

	cards = cards.substr(cards.find(":") + 1);

	while (cards.size() != 2) {

		Card card(cards.substr(0, cards.find("-")));
		myCards.push_back(card);
		cards = cards.substr(cards.find("-") + 1);
	}
	Card card(cards);
	myCards.push_back(card);

	lowestValue = 14;
	for (std::vector<Card>::iterator iter = myCards.begin(); iter != myCards.end(); iter++) {
		if (CardMapping::mymap[iter->getRank()] < lowestValue)
			lowestValue = CardMapping::mymap[iter->getRank()];
	}
}

bool lowToHighComparison(Card a, Card b) {

	return (CardMapping::mymap[a.getRank()] < CardMapping::mymap[b.getRank()]);
}

void Hand::sortLowToHigh() {

	std::sort(myCards.begin(), myCards.end(), lowToHighComparison);
}

const int Hand::getLowestValue() const {

	return lowestValue;
}

Card Hand::getCard(int index) {

	return myCards[index];
}

void Hand::printHand(){

	std::cout << "My hand is: ";
	for (std::vector<Card>::iterator it = myCards.begin(); it != myCards.end(); it++)
		std::cout << it->toString() << " ";

	std::cout << std::endl;
}