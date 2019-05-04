#include "Location.hxx"
#include "Character.hxx"


std::string Bomb::useItem( Character * newCharacter, Location * newLocation )
{
	if( this->status() != true )
		return "Bomb not enabled\n";

	std::string uses = ItemDecorator::useItem( newCharacter, newLocation );
	newLocation->removeItem(getName());
	uses += "Bomb explodes\n";
	uses += newLocation->distributeMagic( 5 );

	return uses;
}


std::string Bomb::receiveMagic( const unsigned int newPoints )
{
	this->status( true );
	std::string receives = ItemDecorator::receiveMagic( newPoints );	
	return receives;
}