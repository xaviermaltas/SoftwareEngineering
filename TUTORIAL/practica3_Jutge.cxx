/*
    JUTGE 3
	Xavier Maltas Tarridas -> 183809
	Oscar Crespo Sanchez -> 174888
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <sstream>

//TODO ESTE CODIGO LO HEMOS COGIDO DE NUESTRA PRACTICA, PERO HEMOS CAMBIADO ALGUN NOMBRE PARA HACER MÁS ENTENDIBLE ESTA ENTREGA

using namespace std;

class ItemNotFound;
class LocationNotFound;
class CharacterNotFound;
class Item;
class Character;
class Location;
class World;


typedef vector<Item *> Items;
typedef vector<Character *> Characters;
typedef vector<Location *> Locations; 



class ItemNotFound :  public exception
{
    public:
        const char * what() const throw () { return "The item does not exist"; }
};

class LocationNotFound :  public exception
{
    public:
        const char * what() const throw () { return "The location does not exist"; }
};

class CharacterNotFound :  public exception
{
    public:
        const char * what() const throw () { return "The character does not exist"; }
};


class Item{

    string _name;
    unsigned int _level;

    public:
        Item() 
            :_name("unknown"),
             _level(50u)
        {}	

        const string & getName() const { return _name; }

        void setName(const string &name) { _name = name; }

        const unsigned int & level() const { return _level; }

        void level(const unsigned int &level) { _level = level; }

        string description () 
        {
            stringstream ss;
            ss << getName() << " [" << level() << "]";
            return ss.str();
        }

};


class Character{

    string _name;
    unsigned int _level;
    Location * _location;

    public:
        Character()
            :_name("unknown"), 
             _level(0u),
             _location(0)
        {}			

        const string & name() const { return _name; }

        void name(const string &name) { _name = name; }

        const unsigned int & level() const { return _level; }

        void level(const unsigned int &level) { _level = level; }

        void locateAt( Location & newLocation );

};

 
class Location{


    string _name;
    Items _items;
    Characters _characters;


    public:
        Location()
                :_name("unknown")
        { }	

        ~Location(){
            for(Items::iterator it = _items.begin(); it!= _items.end(); it++){ delete *it; }
        }	

        const string & name() const { return _name; }

        void name(const string &name) { _name = name; }	

        string description()
        {
            string description = "Location: " + _name + "\n";
            description += items();
            description += characters();
            return description;
        }

        void addItem(const string &name, unsigned level){
            Item* item = new Item();
            item->setName(name);
            item->level(level);
            _items.push_back(item);
        }

        string items() const{
            string out = "";
            for(Items::const_iterator it = _items.begin(); it!= _items.end(); it++){ out += "\tItem: " + (*it)->description() + "\n"; }
            return out;
        }

        Item & findItem(const string &findName){
            for(Items::const_iterator it = _items.begin(); it!= _items.end(); it++){ if((*it)->getName() == findName){ return (**it); } }
            throw ItemNotFound();
        }

        void placeCharacter(Character & placedCharacter){
            Character * characterPl = &placedCharacter;
            _characters.push_back( characterPl );
        }

        string characters(){
            string characters;
            for(Characters::iterator it = _characters.begin(); it != _characters.end(); ++it){ characters += "- " + (*it)->name() + " is here.\n"; }
            return characters;
        }

        Character & findCharacter(const string &findName){
            for(Characters::iterator it = _characters.begin(); it!= _characters.end(); it++){ if((*it)->name() == findName){ return (**it); } }
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
		
};



void Character::locateAt (Location & location)
{
    if (_location == 0) { location.placeCharacter(*this); }
    else 
    {
        _location->unplaceCharacter(*this); 
        location.placeCharacter(*this);
    }
    _location = &location;
}


class World{
    
    Characters _characters;

    public:

        Locations _locations;
        
        World() {}

        ~World(){
            for(Locations::iterator it = _locations.begin(); it!= _locations.end(); it++){ delete *it; }
            for(Characters::iterator it = _characters.begin(); it!= _characters.end(); it++){ delete *it; }
        }

        void addLocation (const string & newLocation)
        {
            Location* location = new Location();
            location->name(newLocation);
            _locations.push_back(location);
        }

        string locations () const
        {
            string locations = "";
            for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); it++ ){ locations += (*it)->name() + "\n"; }
            return locations;
        }

        string locationDetails( const string & details)
        {
            string locations;
            for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); it++ ){
                if ((*it)->name() == details){
                    locations += (*it)->description();
                    return locations; 
                }
            }
            throw LocationNotFound();
        }

        void addItemAtLocation(const string &newLocation, const string &newItem2, unsigned requiredLevel){
            bool aux= false;
            for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); it++ ){ 
                if ((*it)->name() == newLocation){
                    (*it)->addItem(newItem2, requiredLevel);
                    aux = true;
                }
            }
            if(aux==false) {throw LocationNotFound();}

        }

        Location & findLocation ( const string & newLocation )
        {
            if ( _locations.empty() != true ) {	 for ( Locations::iterator it = _locations.begin(); it != _locations.end();++it ){ if( (*it)->name() == newLocation ){ return (**it); } } }
            throw LocationNotFound();
        }

        void addCharacter (const string & newCharacter, unsigned level)
        {
            Character* character = new Character();
            character->name(newCharacter);
            character->level(level);
            _characters.push_back(character);
        }



        void placeCharacter (const string &character,const string &location)
        {
            int flagCharacterCheck = 0;
            for (Characters::const_iterator it = _characters.begin();it != _characters.end();it++ ){
                if((*it)->name() == character){
                    findCharacter(character).locateAt(findLocation(location));
                    flagCharacterCheck=1;
                }
            }
            if(flagCharacterCheck==0){ throw CharacterNotFound(); }
        }


        Character & findCharacter ( const string & character )
        {
            if ( _characters.empty() != true ) { for ( Characters::iterator it = _characters.begin(); it != _characters.end(); ++it ){ if( (*it)->name() == character ){ return (**it); } } }
            throw CharacterNotFound();
        }

};



int main() {
    
    	World world;

//LECTURA LOCALITZACIONS

	int num_locations;
	string location;
	cin>>num_locations>>ws;
    
	for(int i=0;i<num_locations;i++){
		getline(cin,location);
		world.addLocation( location );
	}
//LECTURA CHARACTERS
	int num_characters, characters_level;
   
	string character;
    
	cin>>num_characters>>ws;
	for(int i=0;i<num_characters;i++){
		getline(cin,character, '-');
		cin>>characters_level;
		cin.ignore(100, ' ');

		getline(cin,location);
		world.addCharacter( character, characters_level );
		world.placeCharacter( character, location );
	}
//LECTURA ITEMS
	int num_items, item_level;
	string item;
   
	cin>>num_items>>ws;
	for(int i=0;i<num_items;i++){
		//guardamos el nombre del item hasta el caracter '-'
		getline(cin,item, '-');
		//lo que resta del get line, lo ponemos ens la variable item_level
		cin>>item_level;
		//ignoramos els espacio que hay despues del valor del level
		cin.ignore(100, ' ');
		//guardamos el nombre de la localizacion en la variable 'location'
		getline(cin,location);
		//seguidamente añadimos el item a la localizacion
		world.addItemAtLocation(location,item,item_level);  
	}
//BUCLE FINAL
	for ( Locations::const_iterator it = world._locations.begin(); it != world._locations.end(); it++ ){ cout<<world.locationDetails((*it)->name()); }

    
}
