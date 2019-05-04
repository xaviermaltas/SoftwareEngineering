#ifndef CharacterDamage_hxx
#define CharacterDamage_hxx

#include <iostream>
#include "Character.hxx"
#include <stdio.h>

class CharacterDamage : public Character
{
	
	public:
		CharacterDamage ( std::string newName, unsigned int newLevel) 
		{  
			_name = newName;
			_level = newLevel;
		}


		std::string receiveMagic(unsigned int damg)
		{
			//printf("llego");
			damage(damg);  

			std::stringstream damageChar;
			damageChar << damg;
			return Character::receiveMagic(damg) + _name  + " takes " + damageChar.str() + " damage\n";
		}

};

#endif
