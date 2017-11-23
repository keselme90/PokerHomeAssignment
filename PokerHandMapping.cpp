#include "PokerHandMapping.h"

/**
*Initialization of static variable
*Each possible poker hand gets a score from best to worst
*/
std::map<std::string, int> HandMapping::handMap = { {"Straight Flush", 9}, {"4-of-a-Kind", 8}, {"Full House", 7},
													{"Flush", 6}, {"Straight", 5}, {"3-of-a-Kind", 4}, {"Two Pair",3}, {"One Pair", 2}, 
													{"High Card", 1 } };