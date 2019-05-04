#ifndef LOCATION_HXX
#define LOCATION_HXX

#include "Item.hxx"
#include "Character.hxx"
#include "AbstractItem.hxx"
#include "Trap.hxx"
#include "Potion.hxx"
#include "Bomb.hxx"
#include "MyException.hxx"
#include "CharacterDamage.hxx"
#include <vector>


typedef std::vector<Character *> Characters;
typedef std::vector<AbstractItem *> Items;
  

// Realizado en clase con el tutor Sebastian Marichal
class Location{

protected: 
	std::string _name;      
	Location* _north;
	Location* _south;  
	Location* _west;
	Location* _east;
	Items _items;
	Characters _characters;

	public:
		Location()
			:_name("unknown"),_north(NULL), _south(NULL), _west(NULL), _east(NULL)
		{}		
		
		Location ( const std::string &newName ) {
		_name = newName;
		_north = NULL;
		_south = NULL;
		_east = NULL;
		_west = NULL;
	}

		const std::string & name() const
		{
			return _name;
		}

		void name(const std::string &name) 
		{
			_name = name;
		}	

		
		std::string description()
		{
			
			std::string description = "Location: " + _name + "\n";
			description += connections();
			description += items();
			description += characters();
			
			return description;
			
		}

		std::string connections () const 
		{
			std::string connections = "";

			if (_north != NULL ){connections += "\tNorth: " + _north->name() + "\n";}
			if (_south != NULL ){connections += "\tSouth: " + _south->name() + "\n";}
			if (_east != NULL ){connections += "\tEast: " + _east->name() + "\n";}
			if (_west != NULL ){connections += "\tWest: " + _west->name() + "\n";}

			return connections; 
		}

		
		void addItem(const std::string & name,const unsigned int level){
			AbstractItem * item = new Item(name, level);
			_items.push_back(item);
		}

		
		std::string items() const{
			std::string out = "";
			for(Items::const_iterator it = _items.begin(); it!= _items.end(); it++){
				out += "\tItem: " + (*it)->description() + "\n";
			}
			return out;
			
		}
		
		
		AbstractItem & findItem(const std::string &findName){
			for(Items::const_iterator it = _items.begin(); it!= _items.end(); it++){
				if((*it)->getName() == findName){
					return (**it);			
				}
			}
			throw ItemNotFound();
			
		}
		
		
		void placeCharacter(Character & placedCharacter){
			Character * characterPl = &placedCharacter;
			_characters.push_back( characterPl );
		}

		

		std::string characters(){
			std::string characters;

			for(Characters::iterator it = _characters.begin(); it != _characters.end(); ++it){
				characters += "- " + (*it)->name() + " is here.\n";
			}
			return characters;
		}
		
			
		Character & findCharacter(const std::string &findName){
			for(Characters::iterator it = _characters.begin(); it!= _characters.end(); it++){
				if((*it)->name() == findName){
					return (**it);			
				}
			}
			throw CharacterNotFound();
			
		}
		
		
		void unplaceCharacter(Character & unplacedCharacter){
			for(Characters::iterator it = _characters.begin(); it!= _characters.end(); it++){
				if((*it)->name() == unplacedCharacter.name()){
					it = _characters.erase(it);
					return;			
				}
			}
			throw CharacterNotFound();
			
		}
		
		
		void connectNorth(Location &norte) 
		{
			_north = &norte;
		}
		
		Location* north() {
			return _north;
		}
	
		void connectSouth(Location &sur) 
		{
			_south = &sur;
		}
	
		Location* south() {
			return _south;
		}
		
		void connectWest(Location &west) 
		{
			_west = &west;
		}
	
		Location* west() {
			return _west;
		}
		
		void connectEast(Location &east) 
		{ 
			_east = &east;
		}
		
		Location* east() {
			return _east;
		}

		std::string distributeMagic ( int npts )
		{
			std::string d = ""    ;

			for ( Characters::iterator it = _characters.begin(); it != _characters.end(); ++it ){
				d += (*it)->receiveMagic( npts );
			}

			for ( Items::const_iterator it2 = _items.begin(); it2 != _items.end(); ++it2 ){		
				d += (*it2)->receiveMagic( npts );	
			}

			return d;
		}

		void addTrap(const std::string & nName, unsigned int nPts )
		{
			AbstractItem * itemAbstracto = new Trap(new Item(nName,nPts ));
			_items.push_back(itemAbstracto);

		}


		void removeItem(const std::string & remItem){
            for(Items::iterator it = _items.begin(); it!= _items.end(); it++){
                if((*it)->getName() == remItem){
                    it = _items.erase(it);
                    return;
                }
            }
            throw ItemNotFound();

        }

        void addPotion ( const std::string & newName, unsigned int newPoints )
		{
			
			AbstractItem * absItem = new Potion( new Item(newName, newPoints) ) ;
			_items.push_back( absItem );
		}

		void addBomb ( const std::string & newName, unsigned int newPoints )
		{
			AbstractItem * absItem = new Bomb(new Item(newName, newPoints) );

			_items.push_back( absItem );
		}

		~Location(){
			for(Items::iterator it = _items.begin(); it!= _items.end(); it++){
				delete *it;
			}
		}	

		

};
 

#endif
