#include "Location.hxx"
#include "Character.hxx"

std::string Potion::useItem( Character * newCharacter ,  Location * newLocation )
{
	std::string uses = ItemDecorator::useItem( newCharacter, newLocation );
	newLocation->removeItem(getName());
	return uses +  newCharacter->name() + newCharacter->cure( 5 );
}
  