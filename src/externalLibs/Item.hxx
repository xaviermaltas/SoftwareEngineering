#ifndef ITEM_HXX
#define ITEM_HXX 

#include <sstream>

#include "AbstractItem.hxx"



class Character;
class Location;

class Item : public AbstractItem{
	
	protected:
		std::string _name;
		unsigned int _level;
		bool _hasItem;
		bool estado;

	public:
		Item () {
		_name = "unknown";
		_level = 75;
		estado = false;
		_hasItem = false;
		}

		Item ( const std::string & newName, const unsigned int newLevel ) {
			_name = newName;
			_level = newLevel;
			estado = false;
		}

		
		const std::string & getName() const
		{
			return _name;
		}


		void setName(const std::string &name) 
		{
			_name = name;
		}

		
		const unsigned int & level() const
		{ 
			return _level;
		} 

		void level(const unsigned int &level) 
		{     
			_level = level;
		}
		 
		
		const bool & hasItem() const
		{
			return _hasItem;
		}

		void hasItem(const bool &hasItem) 
		{
			_hasItem = hasItem;
		}

		
		std::string description () 
   		{
       		 	std::stringstream stream;    
        		stream << getName() << " [" << level() << "]";
         		return stream.str();
   		}

   		std::string useItem( Character * newCharacter,  Location * location);

		std::string receiveMagic ( const unsigned int npts )
		{
			std::stringstream points;
			points << npts;
 
			return _name + " receives " + points.str() + " magic points\n";
		}

		bool status () 
		{ 
			return estado; 
		}

		void status ( bool nEstado ) 
		{ 
			estado = nEstado; 
		}
 
};
  

#endif
