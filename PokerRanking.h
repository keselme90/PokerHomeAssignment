#pragma once
#include "Hand.h"
class PokerRanking {

public:
	static bool checkIfStraightFlush(Hand hand);
	static bool checkIfFourOfAKind(Hand hand);
	static bool checkIfFullHouse(Hand hand);
	static bool checkIfFlush(Hand hand);
	static bool checkIfThreeOfAKind(Hand hand);
	static bool checkIfTwoPair(Hand hand);
	static bool checkIfOnePair(Hand hand);
};