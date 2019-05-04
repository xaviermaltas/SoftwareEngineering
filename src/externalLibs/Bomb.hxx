#ifndef Bomb_hxx
#define Bomb_hxx

#include <iostream>
#include "ItemDecorator.hxx"

class Bomb : public ItemDecorator {
	
public:
	Bomb( AbstractItem * absItem ) : ItemDecorator(absItem){}
	
	std::string useItem( Character * newCharacter, Location * newLocation  );
	std::string receiveMagic( const unsigned int newPoints );
};

#endif

