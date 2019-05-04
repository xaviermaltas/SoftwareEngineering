#ifndef ItemDecorator_hxx
#define ItemDecorator_hxx

#include "AbstractItem.hxx"

class ItemDecorator : public AbstractItem {
	
protected:

	AbstractItem * itemAbstracto;

public:

	ItemDecorator ( AbstractItem * item ){
		itemAbstracto = item;
	}


	const std::string & getName() const
	{
		return itemAbstracto->getName();
	}


	void setName(const std::string &name) 
	{
		return itemAbstracto->setName(name);
	}

	
	const unsigned int & level() const
	{ 
		return itemAbstracto->level();
	} 

	void level(const unsigned int &level) 
	{     
		return itemAbstracto->level(level);
	}
	 
	
	const bool & hasItem() const
	{
		return itemAbstracto->hasItem();
	}

	void hasItem(const bool &hasItem) 
	{
		return itemAbstracto->hasItem(hasItem);
	}

	
	std::string description () 
	{
 		return itemAbstracto->description();
	}

	
	std::string useItem(Character * newCharacter,  Location * location)
	{
		return itemAbstracto->useItem(newCharacter, location);
	}

	std::string receiveMagic ( const unsigned int npts )
	{
		return itemAbstracto->receiveMagic(npts);
	}

	bool status () 
	{ 
		return itemAbstracto->status(); 
	}

	void status ( bool nEstado ) 
	{ 
		return itemAbstracto->status(nEstado); 
	}


	~ItemDecorator()
	{
		if ( itemAbstracto != NULL ) 
			delete itemAbstracto; 
	}
	
};

#endif

