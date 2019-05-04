#ifndef CHARACTER_HXX
#define CHARACTER_HXX 

#include <sstream>   

class Location;

 
class Character{

	protected:
		std::string _name;
		unsigned int _level;
		unsigned int _life;
		unsigned int _damage;
		unsigned int _cure;

		Location * loc_;



	public:
		
		Character()
			:_name("unknown"), _level(0u), _life(10u), loc_(0)     
		{
 			// TO DO
		}	

	
		const std::string & name() const
		{
			return _name;
		}

		void name(const std::string &name) 
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

		std::string damage(const unsigned int &damage) 
		{
			if(damage > _life ){ _life = 0; }
			else { _life = _life-damage; }

			std::stringstream ss;
			ss << damage;
			return this->name() + " takes " + ss.str() + " damage\n";
		}

		const unsigned int & life() 
		{
			return _life;
		}

		void life(const unsigned int &life) 
		{
			_life = life;
		}


		std::string cure(const unsigned int &cure) 
		{
			if(_life==10){ _life = _life; }
			else{ _life = _life + cure; }
			std::stringstream ss;
			ss << cure;

			return " gains " + ss.str() + " life\n";
		}

		void locateAt( Location & newLoc );
		Location * playerLocations() const { return loc_; }

 
		virtual std::string receiveMagic(unsigned int points)
		{
			std::stringstream ss;
			ss << this->name() << " receives " << points << " magic points\n";
			return ss.str();
		}

		



		virtual ~Character(){};



};

#endif
