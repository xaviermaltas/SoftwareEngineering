#ifndef MYEXCEPTION_HXX
#define MYEXCEPTION_HXX


class CharacterNotFound :  public std::exception
{
	public:
	const char * what() const throw ()
	{
		return "The character does not exist";
	}
};



class ItemNotFound :  public std::exception
{
	public:
	const char * what() const throw ()
	{
		return "The item does not exist";
	}
};



class LocationNotFound :  public std::exception
{
	public:
	const char * what() const throw ()
	{
		return "The location does not exist";
	}
};


#endif

