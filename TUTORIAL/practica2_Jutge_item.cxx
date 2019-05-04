/*


PRACTICA 2:


	ALUMNES			NIA


 Xavier Maltas -> 183809

 Oscar Crespo -> 174888
*/


#ifndef items_hxx
#define items_hxx
//PER PODER UTILITZAR TANT VECTORS I STRINGS A LA PRACTICA HEM HAGUT D'AFEGIR ELS INCLUDES NECESARIS
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
    
class Item
{
    public: 
    	void name(std::string theName){
    		_name = theName;
    	}
    	std::string& name(){
    		return _name;
    	}

	void level(std::string theLevel){
    		_level = theLevel;
    	}
    	std::string& level(){
    		return _level;
    	}
   
    private:
    	std::string _name;
	std::string _level;
    };

#endif

typedef std::list<Item*> Items; //Declaraciรณ d'una llista anomenada Locations de tipus Animal(super-classe)

int main(void){
        
    Items items;  //Creaciรณ d'una instancia animals de tipus Animals

    	int N;
	int barSpace;
    	std::string line;
	std::string nomItem;
	std::string linewtbarSpace;
	//int level;
	std::string levell;

    std::cin>> N >> std::ws;  //std::cin llegeix i ho guarda a N el que entrem per pantalla (usuari)

    for(int i = 0; i<N; i++){  //N es el numero que hem entrat per pantalla

        std::getline( std::cin, line); //guardem total la linia llegida a la variable line
        barSpace = line.find("-");
	linewtbarSpace = line.substr(barSpace);
	nomItem = line.substr(0,barSpace);
	levell = linewtbarSpace.substr(1);
	Item *Itemm = new Item();
	Itemm->name(nomItem);
	Itemm->level(levell);
	items.push_back(Itemm);
    }


    for (Items::iterator it=items.begin(); it!=items.end(); it++){
        std::cout << "Item: " << (*it)->name() <<" ["<< (*it)->level()<<"]"<<std::endl;
    }

    return 0;

}
