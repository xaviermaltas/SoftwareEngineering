
#ifndef Potion_hxx
#define Potion_hxx

#include <iostream>
#include "ItemDecorator.hxx"

class Potion : public ItemDecorator {
	
public:

	Potion( AbstractItem * absItem ) : ItemDecorator(absItem){}
	
	std::string useItem( Character * newCharacter ,  Location * newLocation);
	
};

#endif
