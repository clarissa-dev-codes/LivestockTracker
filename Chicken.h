//chicken class
#ifndef CHICKEN_H
#define CHICKEN_H

#include <iostream>
#include <string>
#include <vector>
#include "Livestock.h"

using namespace std;

struct Chicken
{
	Animal chicken;
	string colorBand;
	string gender;
	int coopID = 1000000; //the whole ID

	
};

class ChickenList : public Livestock
{
private:
	vector<Chicken> chick;

public:

	ChickenList();
	ChickenList(const string& filename);

	int setCoopID(string breed, string gender, string colorBand);
	int getCoopID(size_t flock) const;

	void getInfo() const override;

	void addNewChicken();
	void addHelper(const Chicken& newChicken);
	Chicken& findChickenID(int id);

	int getFlockSize();

	void loadFromFile(const string& filename);
	void addToFile(const string& filename, const Chicken& chickPtr);
	void saveToFile(const string& saveFile) const;
	void saveOne(const string& saveFile, const Chicken& chick);


	void moveToSoldList(const string& soldFile, int id);
	void moveToDeadList(const string& deadFile, int id);
	void removeFromList(int id);

	void printsoldChickens() const;
	void printdeadChickens() const;


};

#endif