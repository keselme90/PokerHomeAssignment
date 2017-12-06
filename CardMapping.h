#ifndef CARDMAPPING_H
#define CARDMAPPING_H

#include<map>

/**
* Class with a static variable to help to map card rank to it's numeric value.
*/
class CardMapping {

public:
	static std::map<char, int> mymap;
};

#endif