//goat class
#ifndef GOAT_H
#define GOAT_H

#include <iostream>
#include <string>
#include <vector>
#include "Livestock.h"

using namespace std;

struct Manage
{
	int bornCount;
	int boughtCount;
	int soldCount;
	int deadCount;
};

struct Goat
{
	Animal goat; //should inherit from livestock
	int goatID = 3000000;
};



class GoatList : public Livestock
{
private:
	vector<Goat> goats;
	

public:
	GoatList();
	GoatList(const string& filename);

	void addNewGoat();
	void addHelper(const Goat& newGoat);

	Goat& findGoatID(int id);

	int getHerdSize();

	int setGoatID(string breed, string gender, string other);
	int getGoatID(size_t size) const;

	void getInfo() const override;

	void loadFromFile(const string& filename);
	void addToFile(const string& soldFile, const Goat& goatPtr);
	void saveToFile(const string& saveFile);
	void saveOne(const string& saveFile, const Goat& goat);

	void moveToSoldList(const string& soldFile, int id);
	void moveToDeadList(const string& deadFile, int id);

	void removeFromList(int id);

	void printsoldGoats() const;
	void printdeadGoats() const;
	
};

#endif