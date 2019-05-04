
#ifndef Cure_hxx
#define Cure_hxx

#include <iostream>
#include "Character.hxx"

class Cure : public Character {

public:

	Cure ( const std::string newName, const unsigned int newLevel ) {
		_name = newName;
		_level = newLevel;
	} 

	std::string receiveMagic ( unsigned int newPoints )
	{
		cure( newPoints );

		std::stringstream points;
		points << newPoints;

		return 	Character::receiveMagic( newPoints ) + _name + " gains " + points.str() + " life\n";
	}

};

#endif

