//livestock imp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Livestock.h"

using namespace std;


/*----------------------------------
		UML stuff
-----------------------------------*/
void Livestock::markSold()
{
	setSold(true);
	
}
void Livestock::markDead()
{
	setStatus(false);
	
}


void Livestock::setName(string Name)
{
    animal.name = Name;
}
void Livestock::setStatus(bool stat)
{
    animal.status = (stat ? "alive" : "dead");
}
void Livestock::setBirthDate(string birth)
{
    animal.birthDate = birth;
}
void Livestock::setGender(string Gender)
{
    animal.gender = Gender;
}
void Livestock::setSold(bool Sold)
{
    animal.sold = Sold;
}
void Livestock::setBreed(string Breed)
{
    animal.breed = Breed;
}


/*----------------------------------
        Getters
-----------------------------------*/

string Livestock::getName() const
{
    return animal.name;
}
string Livestock::getStatus() const
{
    return animal.status;
}
string Livestock::getBirthDate() const
{
    return animal.birthDate;
}

bool Livestock::getSold() const
{
    return animal.sold;
}

string Livestock::getGender() const
{
    return animal.gender;
}

string Livestock::getBreed() const
{
    return animal.breed;
}


