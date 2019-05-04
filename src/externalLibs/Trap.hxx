#ifndef Trap_hxx
#define Trap_hxx

#include "ItemDecorator.hxx"

class Trap : public ItemDecorator {
	
public:

	Trap( AbstractItem * absItem ) : ItemDecorator(absItem){}
	
	std::string useItem(Character * newCharacter, Location * location );
	 
}; 

#endif
