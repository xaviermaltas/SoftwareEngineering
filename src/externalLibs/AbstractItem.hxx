#ifndef AbstractItem_hxx
#define AbstractItem_hxx

#include "Character.hxx"
#include <iostream>
#include <string>
#include <vector>

class AbstractItem {

public:


		virtual const std::string & getName() const=0;
		virtual void setName(const std::string &name) =0;		
		virtual const unsigned int & level() const=0;
		virtual void level(const unsigned int &level) =0;
		virtual const bool & hasItem() const=0;
		virtual void hasItem(const bool &hasItem) =0;		
		virtual std::string description () =0;
   		virtual std::string useItem(Character * newCharacter, Location * location)=0;
		virtual std::string receiveMagic ( const unsigned int npts )=0;
		virtual bool status ()=0;
		virtual void status ( bool nEstado ) =0;
		virtual ~AbstractItem() {}; 
 


};


#endif
