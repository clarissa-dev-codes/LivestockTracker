//horse class
#ifndef HORSE_H
#define HORSE_H

#include <iostream>
#include "Livestock.h"

using namespace std;

//all his horses are American Quarter Horses
//so the next number in the ID should be a 1

struct Horse
{
	Animal horse;

	int ID = 4100000;
	string location;
	

};

class HorseList : public Livestock
{
private:
	vector<Horse> horses;
	int MSHerd;
	int ALHerd;
	int MikeHerd;
	int JerryHerd;

	

public:
	//constructor
	HorseList();
	HorseList(const string& filename);	

	void addNewHorse();
	void addHelper(const Horse& newHorse);

	Horse& findHorseID(int id);

	int getHerdSize();

	int setID(string Gender, string Location);
	int getID(size_t size) const;

	void getInfo() const override;

	void loadFromFile(const string& filename);
	void addToFile(const string& soldFile, const Horse& horsePtr);
	void saveToFile(const string& filename) const;
	void saveOne(const string& saevFile, const Horse& horse);

	void moveToSoldList(const string& soldFile, int id);
	void moveToDeadList(const string& deadFile, int id);
	void moveLocation(const string& locationFile, int id, string newLocation);

	void removeFromList(int id, const string& filename);

	void printsoldHorses() const;
	void printdeadHorses() const;
	
	void printLocation(const string& locationFile) const;

	
};

#endif