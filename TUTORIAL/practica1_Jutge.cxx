/*


PRACTICA 1:


	ALUMNES			NIA


 Xavier Maltas -> 183809

 Oscar Crespo -> 174888
*/

#ifndef animals_hxx
#define animals_hxx
//PER PODER UTILITZAR TANT VECTORS I STRINGS A LA PRACTICA HEM HAGUT D'AFEGIR ELS INCLUDES NECESARIS
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
    
class Animal
{
    public: 
    	virtual void writeSpecies() const{
    		std::cout << "...undefined..." << std::endl;
    	}
    	void name(std::string theName){
    		_name = theName;
    	}
    	std::string& name(){
    		return _name;
    	}

        void afegeixAmic(std::string Amic){
    		vamics.push_back(Amic);
    	}
    	std::string afegeixAmic(){
    		if(vamics.size()!=0){
                std::string afegeixAmic = vamics.at(0); 
                for(int i = 1; i<vamics.size(); i++){
                    afegeixAmic.append(", " +vamics.at(i));
                }
                return afegeixAmic;
            }
            else {
                return "no te amics";
            }
    	}
   
    private:
    	std::string _name;

    	//Definim el vector de strings de amics
        std::vector <std::string> vamics = std::vector <std::string>(); 
            
    };


//subclase de Animal.
class Elephant : public Animal
{
public:
	void writeSpecies() const
	{
		std::cout << "elephant" << std::endl;
	}
};
//subclase de Animal
class Frog : public Animal
{
public:
	void writeSpecies() const
	{
		std::cout << "frog" << std::endl;
	}
};
//subclase de Animal
class Cat : public Animal
{
public:
	void writeSpecies() const
	{
		std::cout << "cat" << std::endl;
	}
};

#endif

typedef std::list<Animal*> Animals; //Declaració d'una llista anomenada Animals de tipus Animal(super-classe)

int main(void){
        
    Animals animals;  //Creació d'una instancia animals de tipus Animals

    int N;
    std::string line;
    std::string nomAnimal;
    std::string tipusAnimal;
    std::string cadAux;
    std::string linewtBlankSpace;
    int blankSpace;

    std::cin>> N >> std::ws;  //std::cin llegeix i ho guarda a N el que entrem per pantalla (usuari)

    for(int i = 0; i<N; i++){  //N es el numero que hem entrat per pantalla
        std::getline( std::cin, line); //guardem total la linia llegida a la variable line
        blankSpace = line.find(" "); //cerquem la posició del espai vuit entre <tipus> <nomAnimal>
        linewtBlankSpace = line.substr(blankSpace); 
        tipusAnimal = line.substr(0,blankSpace); //Declarem que de la linia llegida, el tipus d'Animal correspon a el elemnt entre el inici i el blankSpace
        nomAnimal = linewtBlankSpace.substr(1); //El nom del animal es el que queda a la cadAux
        cadAux = nomAnimal;  //A la cadAux tambe hi guardem el nom del animal

        if(tipusAnimal=="Animal"){
            Animal *nomAnimal = new Animal(); 
            nomAnimal->name(cadAux); 
            animals.push_back(nomAnimal); 
        }else if(tipusAnimal=="Elephant"){
            Elephant *nomAnimal = new Elephant();
            nomAnimal->name(cadAux);
            animals.push_back(nomAnimal);
        }else if(tipusAnimal=="Frog"){
            Frog *nomAnimal = new Frog();
            nomAnimal->name(cadAux);
            animals.push_back(nomAnimal);
        }else if(tipusAnimal=="Cat"){
            Cat *nomAnimal = new Cat();
            nomAnimal->name(cadAux);
            animals.push_back(nomAnimal);
        }else{
            std::cout << "Hi ha alguna entrada erronea" << std::endl; 
        }   
    }

    int K;
    int barSpace;

    //Aquestes variables de tipo string les declarem ja que les necesitarem per poder guardar els noms que entrem i que necesitarem en el bucle for
    std::string linewtBarSpace;
    std::string nomAmic1;
    std::string nomAmic2;


    std::cin>> K >> std::ws; //Aqui es el mateix que a dalt, s'entra un valor que el guardarem a K

    for(int j = 0; j<K ; j++){ 
        std::getline( std::cin, line ); // el que fa std::getline és agafar els caracters de la linia
        barSpace = line.find("-"); //la paraula clau find el que fa es buscar el que li passem, en aquest cas el "-" i ho apliquem a line que es on em guardat abans tota la linia
        linewtBarSpace = line.substr(barSpace); //substr el que fa es agafar desde el que li entrem, en aquest cas el barspace y ho guardem a linewtbarsapce
        nomAmic1 = line.substr(0,barSpace);
        nomAmic2 = linewtBarSpace.substr(1);

        //Bucle on fem que l'amistat sigui reciproca
        for (Animals::iterator it=animals.begin(); it!=animals.end(); it++) 
        {
            if(nomAmic1 == (*it)->name()){ //Cerca dins el vector animals
                (*it)->afegeixAmic(nomAmic2);
                for (Animals::iterator at=animals.begin(); at!=animals.end(); at++){
                    if(nomAmic2 == (*at)->name()){   
                        (*at)->afegeixAmic(nomAmic1);
                    }
                }
                break;
            }
        }
    }

    for (Animals::iterator it=animals.begin(); it!=animals.end(); it++){
        std::cout << (*it)->name() << " is of the species ";
        (*it)->writeSpecies();
        if((*it)->afegeixAmic() != "no te amics"){
            std::cout << (*it)->name() << " is friends with "<<(*it)->afegeixAmic()<<std::endl;
        }

    }

    return 0;

}

