#ifndef WORLD_HXX
#define WORLD_HXX


#include "Item.hxx"
#include "Character.hxx"
#include "Location.hxx"
#include "Cure.hxx" 
#include "Potion.hxx" 
#include "MyException.hxx"
#include "Model.hxx"
#include <vector>

typedef std::vector<Character *> Characters; 
typedef std::vector<Location *> Locations; 


class World : public Model{ 
	
	Locations _locations;
	Characters _characters;
	
	public:

		//World Destructor
		~World(){
			for(Locations::iterator it = _locations.begin(); it!= _locations.end(); it++){
				delete *it;
			}
			for(Characters::iterator it = _characters.begin(); it!= _characters.end(); it++){
				delete *it;
			}
		}

// ------------ LOCATION

		void addLocation (const std::string & newLocation)
		{
			Location* location = new Location();
			location->name(newLocation);
			_locations.push_back(location);
		}//addLocation
	
		//Retorna totes les localitzacions del World
		std::string locations () const
		{
			std::string locations = "";
	
			for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); it++ ){
				locations += (*it)->name() + "\n";
			}
	
			return locations;
		}//locations
		
		//Reserca d'una localització dins del World i treure tota la seva infomació
		std::string locationDetails( const std::string & details){
			
			std::string locations;
			
			for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); it++ ){
				
				if ((*it)->name() == details){
					locations += (*it)->description();
					return locations; 
				}
			}
			throw LocationNotFound();
		}//locationDetails

		void addItemAtLocation(const std::string &newLocation, const std::string &newItem2, unsigned requiredLevel){
			bool aux= false;
			for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); it++ ){
				
				if ((*it)->name() == newLocation){
					(*it)->addItem(newItem2, requiredLevel);
					aux = true;
				}
			}
			if(aux==false) {throw LocationNotFound();}
		}//addItemAtLocation

		void connectNorthToSouth(const std::string &north, const std::string &south){

			for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); it++ ){
				if ((*it)->name() == north){(*it)->connectSouth(findLocation(south));}
				if ((*it)->name() == south){(*it)->connectNorth(findLocation(north));}
			}	
			
		}//connectNorthToSouth
		
		void connectWestToEast(const std::string &west, const std::string &east){

			for ( Locations::const_iterator it = _locations.begin(); it != _locations.end(); it++ ){
				if ((*it)->name() == west){(*it)->connectEast(findLocation(east));}
				if ((*it)->name() == east){(*it)->connectWest(findLocation(west));}	
			}	
			
		}//connectWestToEast
		
		
		Location & findLocation ( const std::string & newLocation )
		{
			if ( _locations.empty() != true )
			{	
				for ( Locations::iterator it = _locations.begin(); it != _locations.end();++it )
					if( (*it)->name() == newLocation )
						return (**it);
			}

			throw LocationNotFound();
		}//findLocation


//--------CHARACTER

		void addCharacter (const std::string & newCharacter, unsigned level)
		{
			Character* character = new Character();
			character->name(newCharacter);
			character->level(level);
			_characters.push_back(character);
		}//addCharacter
		
		std::string characters()const
		{
			std::string characters = "";
	
			for (Characters::const_iterator it = _characters.begin();it != _characters.end();it++ ){
				characters += (*it)->name() + "\n";
			}
	
			return characters; 
		}//characters

		void placeCharacter (const std::string &character,const std::string location)
		{
			int flagCheckCharacter = 0;
			for (Characters::const_iterator it = _characters.begin();it != _characters.end();it++ ){
				if((*it)->name() == character){
					findCharacter(character).locateAt(findLocation(location));
					flagCheckCharacter=1;
				} 
			}
			if(flagCheckCharacter==0){throw CharacterNotFound();}
		}//placeCharacter
     

		Character & findCharacter ( const std::string & character )
		{ 
			if ( _characters.empty() != true )
			{	
				for ( Characters::iterator it = _characters.begin(); it != _characters.end(); ++it )
					if( (*it)->name() == character )
						return (**it);
			}
  
			throw CharacterNotFound();
		}//findCharacter

//---------ITEM

		std::string useItem(const std::string locN, const std::string charN, const std::string itN)
		{	
			findLocation(locN);
			findCharacter(charN);
			findLocation(locN).findItem(itN);
			Location & location = findLocation(locN);
			AbstractItem & item = findLocation(locN).findItem(itN); 
			Character & character = findCharacter(charN);
			
			if(character.level() >= item.level()) { return item.useItem(&character, &location); }
			else return "The level of " + character.name() + " is too low\n";
		}//useItem
   
		std::string distributeMagic ( std::string nLoc, unsigned int nPts )
		{		
			return findLocation( nLoc ).distributeMagic( nPts );
		}//distributeMagic

		void addDamageCharacter(const std::string & nName, unsigned nPts)
		{
			Character * character = new CharacterDamage(nName, nPts);
			
			_characters.push_back(character);
		}//addDamageCharacter

		void addTrapAtLocation (const std::string & nLoc, const std::string & nName, unsigned nPts )
		{		
			return findLocation( nLoc ).addTrap( nName, nPts );
		}//addTrapAtLocation

		void addCureCharacter ( const std::string & newName, unsigned int newPoints )
		{
			Character * cureCharacter = new Cure( newName, newPoints );
			_characters.push_back( cureCharacter );
		}//addCureCharacter

		void addPotionAtLocation ( const std::string & newLocation, const std::string & newName, unsigned newPoints )
		{  
			return findLocation( newLocation ).addPotion( newName, newPoints );
		}//addPotionAtLocation

		void addBombAtLocation ( const std::string & newLocation, const std::string & newName, unsigned newPoints )
		{ 
			return findLocation( newLocation ).addBomb( newName, newPoints );
		}//addBombAtLocation

//---------------------GUI-----------------------//

		Character * player;

		void registerPlayer( const std::string & playerName )
		{
			player = & findCharacter(playerName);
		}//registerPlayer
	 	
	 	std::string locationDetails() const 
	 	{
	 		return player->playerLocations()->description();
	 	}//locationDetails

/*
	 	void move( const std::string & direction ){
			//Fem que el jugador es mogui d'un lloc a un altre
			Location* neighbourLocation = player->currentLocation()->neighbor(direction);
			player->currentLocation( neighbourLocation );		
		}

		std::string useItem( const std::string & itemName ){
			//El player utilitza el item anomenat

			std::string output;
			findLocation( player->currentLocation()->name() );
			findCharacter( player->name() );
			player->currentLocation()->findItem( itemName );
			
			output = player->currentLocation()->useItem( player->name(), itemName );
			
			
			return output;
			//output: El jugador utilitzar el item a la location..
		
		}

		*/

};

#endif 

