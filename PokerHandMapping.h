#pragma once
#include <string>
#include <map>

/**
* Class with a static variable to help to map possible poker hands to their numeric value.
*/
class HandMapping {

public:

	static std::map<std::string, int> handMap;
};
