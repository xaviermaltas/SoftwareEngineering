#include "Location.hxx"


void Character::locateAt (Location & loc)
{
	if (loc_ == NULL) 
	{ 
		loc.placeCharacter(*this); 
	}
	else 
	{
		loc_->unplaceCharacter(*this); 
		loc.placeCharacter(*this); 
	}
	
	loc_ = &loc;
}



