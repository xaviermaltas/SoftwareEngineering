#include "Location.hxx"
#include "Character.hxx"


std::string Trap::useItem( Character * newCharacter, Location * location )
{
	std::string uses = ItemDecorator::useItem( newCharacter, location );
	location->removeItem(getName());
	return uses + newCharacter->damage(5);
}
