//cow class
#ifndef COW_H
#define COW_H

#include <iostream>
#include "Livestock.h"

using namespace std;

struct Cow
{
	Animal cow;

	int ID = 2000000;
	bool registered;
};

class CowList : public Livestock
{
private:
	vector<Cow> cows;
	int regSold;
	int regDead;
	int regBought;

public:
	CowList();
	CowList(const string& filename);

	//no tag numbers

	int getHerdSize();

	void addNewCow();
	void addHelper(const Cow& newCow);

	Cow& findCowID(int id);

	void countSort();
	void bubbleSort();

	int setID(string breed, string gender, bool registered);
	int getID(size_t size) const;

	void getInfo() const override;
	void moveToSoldList(const string& soldFile, int id);
	void moveToDeadList(const string& deadFile, int id);
	void removeFromList(int id, const string& filename);

	void printSoldCows() const;
	void printDeadCows() const;

	void loadFromFile(const string& filename);
	void addToFile(const string& filename, const Cow& newCow);
	void saveToFile(const string& filename) const;
	void saveOne(const string& saveFile, const Cow& newCow);

	
};

#endif