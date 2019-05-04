#include "Location.hxx"
#include "Character.hxx"

std::string Item::useItem ( Character * newCharacter,  Location * location )
{
	return newCharacter->name() + " uses " + (*this).getName() + " at " + location->name() + "\n";
}
