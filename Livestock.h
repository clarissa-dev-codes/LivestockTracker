//livestock class
#ifndef LIVESTOCK_H
#define LIVESTOCK_H

#include <iostream>
#include "Error_Classes.h"

using namespace std;

struct Animal
{
	string status = "Alive"; //alive or dead (alive == true && dead == false)
	string gender; //string doesn't matter whether it's a gelding or a wether or a hen.
	bool sold;
	string birthDate;
	string breed; //can be different depending on the the animal
	string name;

	
};

class Livestock
{
private:
	Animal animal;

	
	
public:
	//constructor
	Livestock() = default;

	//what is on the UML
	void markSold();
	void markDead();

	

	//setters
	
	void setStatus(bool stat);
	void setSold(bool Sold);
	void setBirthDate(string birth);
	void setGender(string gender);
	void setName(string Name);
	void setBreed(string Breed);
	
	

	//getters
	
	
	string getStatus() const;
	string getBirthDate() const;
	bool getSold() const;
	string getGender() const;
	string getName() const;
	string getBreed() const;


	/*--------------------------------------------------------
		Overridable method for getting info about the animal
		Left this message in there just in case there is
		nothing to override 
	--------------------------------------------------------*/
	virtual void getInfo() const
	{
		cout << "Name: " << getName() << endl;
	}
	

	//deconstructor
	~Livestock() = default;

};

#endif