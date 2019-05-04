#ifndef Model_hxx
#define Model_hxx

#include <fstream>
#include <sstream>
#include <QObject>

class Model : public QObject
{
Q_OBJECT

public:

	virtual ~Model() {}

	virtual void addLocation( const std::string & name ) = 0;

	virtual void connectNorthToSouth( const std::string & firstName, const std::string & secondName ) = 0;
	virtual void connectWestToEast( const std::string & firstName, const std::string & secondName ) = 0;

	virtual void addCharacter( const std::string & name, unsigned level ) = 0;
	virtual void addDamageCharacter( const std::string & name, unsigned level ) = 0;
	virtual void addCureCharacter( const std::string & name, unsigned level ) = 0;

	virtual void placeCharacter( const std::string & charName, const std::string locationName ) = 0;

	virtual void addItemAtLocation( const std::string & locName, const std::string & itemName, unsigned requiredLevel ) = 0;
	virtual void addTrapAtLocation( const std::string & locName, const std::string & itemName, unsigned requiredLevel ) = 0;
	virtual void addPotionAtLocation( const std::string & locName, const std::string & itemName, unsigned requiredLevel ) = 0;
	virtual void addBombAtLocation( const std::string & locName, const std::string & itemName, unsigned requiredLevel ) = 0;

	void loadMap( const std::string & filename )
	{
		unsigned level;
		std::ifstream file( filename.c_str() );
		std::string line, token, type, name, location, direction;
		while ( std::getline( file, line ) )
		{
			std::istringstream is( line );
			is >> token;

			if ( token == "Location" )
			{
				is >> name;
				addLocation( name );
			}
			else if ( token == "Character" )
			{
				is >> type >> name >> level;
				if ( type == "Basic" ) addCharacter( name, level );
				else if ( type == "Damage" ) addDamageCharacter( name, level );
				else if ( type == "Cure" ) addCureCharacter( name, level );
			}
			else if ( token == "Item" )
			{
				is >> type >> name >> level >> location;
				if ( type == "Basic" )
					addItemAtLocation( location, name, level );
				else if ( type == "Trap" )
					addTrapAtLocation( location, name, level );
				else if ( type == "Potion" )
					addPotionAtLocation( location, name, level );
				else if ( type == "Bomb" )
					addBombAtLocation( location, name, level );
			}
			else if ( token == "Connection" )
			{
				is >> direction >> name >> location;
				if ( direction == "North" ) connectNorthToSouth( name, location );
				else if ( direction == "West" ) connectWestToEast( name, location );
			}
			else if ( token == "LocateAt" )
			{
				is >> name >> location;
				placeCharacter( name, location );
			}
		}
	}

	virtual void registerPlayer( const std::string & playerName ) = 0;
	virtual std::string locationDetails() const = 0;
	//virtual void move( const std::string & direction ) = 0;
	//virtual std::string useItem( const std::string & itemName ) = 0;

	void start()
	{
		emit modify( locationDetails(), "" );
	}

public slots:
	
	void doMove( const std::string & direction )
	{
		std::string event = "";
		try
		{
			//move( direction );
			event = "You move " + direction;
		}
		catch ( std::exception & e )
		{
			event = "You cannot move " + direction + "!";
		}
		emit modify( locationDetails(), event );
	}

	void doUseItem( const std::string & itemName )
	{
		//std::string event = useItem( itemName );
		//emit modify( locationDetails(), event );
	}

signals:

	void modify( const std::string & locationDetails, const std::string & event );

};

#endif
