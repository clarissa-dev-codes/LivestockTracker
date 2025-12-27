//cow imp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <limits>
#include "Cow.h"
#include "Livestock.h"

using namespace std;

int counter = 000;

CowList::CowList()
{
	
}


CowList::CowList(const string& filename)
{
	ifstream file(filename);

	string line;
	const string delimiter = "***";

	while (getline(file, line))
	{
		if (line == delimiter)
		{
			Cow currentCow;
			string key, value;
			int tempId;
			bool tempBool;

			if (!(file >> key >> key >> tempId)) { break; }

			currentCow.ID = tempId;
			file.ignore(numeric_limits<streamsize>::max(), '\n');

			if (!(file >> key)) { break; }
			getline(file, value);
			currentCow.cow.breed = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentCow.cow.gender = value;

			if (!(file >> key >> key)) { break; }
			if (key == "True")
			{
				currentCow.cow.sold = true;
			}
			else
			{
				currentCow.cow.sold = false;
			}

			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentCow.cow.birthDate = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentCow.cow.status = value;

			if (!(file >> key >> key)) { break; }
			if (key == "True")
			{
				currentCow.registered = true;
			}
			else
			{
				currentCow.registered = false;
			}

			
			this->cows.push_back(currentCow);
		}
	}

	file.close();
}

int CowList::setID(string breed, string gender, bool registered)
{

	int baseID = 0;
	int switchB;
	int switchG;
	int switchR;

	if (breed == "Black Angus")
	{
		switchB = 1;
	}
	else if (breed == "Black Irish")
	{
		switchB = 2;
	}
	else
	{
		switchB = 3;
	}

	if (gender == "Bull")
	{
		switchG = 1;
	}
	else
	{
		switchG = 2;
	}

	if (registered == true)
	{
		switchR = 1;
	}
	else
	{
		switchR = 2;
	}

	switch (switchB)
	{
	case 1:
	{
		baseID = 100000;
		break;
	}
	case 2:
	{
		baseID = 200000;
		break;
	}
	case 3:
	{
		baseID = 300000;
		break;
	}
	}
	
	switch (switchG)
	{
	case 1:
	{
		baseID += 10000;
		break;
	}
	case 2:
	{
		baseID += 20000;
		break;
	}
	}

	switch (switchR)
	{
	case 1:
	{
		baseID += 1000;
		break;
	}
	case 2:
	{
		baseID += 2000;
	}
	}

	baseID += counter;
	counter++;

	return baseID;
	
}
int CowList::getID(size_t herd) const
{
	if (herd < cows.size())
	{
		return this->cows[herd].ID;
	}

	return -1;
}

int CowList::getHerdSize()
{
	return int(cows.size());
}

/*********************************************

		Virutal Override getInfo

 *********************************************/
void CowList::getInfo() const
{
	cout << "-------- Cow Herd Info -----------" << endl;
	for (int i = 0; i < cows.size(); ++i)
	{
		const Cow& currentCow = this->cows[i];
		cout << "Cow ID: " << currentCow.ID << endl;
		cout << "Breed: " << currentCow.cow.breed << endl;
		cout << "Registered: " << (currentCow.registered ? "Yes" : "No") << endl;
		cout << "----------------------------------" << endl;
	}
}


/*********************************************

		Find Cow ID

 *********************************************/

Cow& CowList::findCowID(int searchID)
{
	int low = 0;
	size_t high = cows.size() - 1;

	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (cows[mid].ID == searchID)
		{
			return cows[mid];
		}
		else if (cows[mid].ID > searchID)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
}

/***************************************************

	Counter and Bubble sort

***************************************************/
void CowList::countSort()
{
	if (this->cows.empty())
	{
		return;
	}

	// finds the max and min of the ids
	// supposed to be better than manual
	int maxID = numeric_limits<int>::max();
	int minID = numeric_limits<int>::min();

	for (size_t i = 0; i < this->cows.size(); ++i)
	{
		int current = this->cows[i].ID;
		if (current > maxID)
		{
			maxID = current;
		}
		if (current < minID)
		{
			minID = current;
		}
	}

	int range = maxID - minID + 1;
	vector<int> count(range, 0);
	vector<Cow> output(this->cows.size());

	for (size_t i = 0; i < this->cows.size(); ++i)
	{
		int currentID = this->cows[i].ID;
		count[currentID - minID]++;
	}

	for (int i = 1; i < count.size(); ++i)
	{
		count[i] += count[i - 1];
	}

	for (int i = int(this->cows.size() - 1); i >= 0; --i)
	{
		int currentID = this->cows[i].ID;
		int index = count[currentID - minID];

		output[index] = this->cows[i];
		count[currentID - minID]--;
	}

	this->cows = output;
}

void CowList::bubbleSort()
{
	int n = cows.size();
	bool needSwap;

	for (int i = 0; i < n - 1; i++)
	{
		needSwap = false;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (cows[j].ID > cows[j + 1].ID)
			{
				swap(cows[j], cows[j + 1]);
				needSwap = true;
			}
		}
		if (!needSwap)
		{
			break;
		}
	}
}

/***************************************************

	Adding a new cow to the ist and helper

***************************************************/
void CowList::addHelper(const Cow& newCow)
{
	this->cows.push_back(newCow);

	if (!this->cows.empty())
	{
		countSort();
	}
}

void CowList::addNewCow()
{
	
	Cow newCow;
	string inputBreed;
	string inputGender;
	string inputBirth;
	string registered;
	string option;
	bool isRegister;
	string answer;
	bool beenBought = false;
 
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Please enter the breed of the new cow (Black Angus/Black Irish/Cross: ";
	getline(cin, inputBreed);
	newCow.cow.breed = inputBreed;

	cout << "Please enter the gender of the new cow (Bull/Heifer):  ";
	getline(cin, inputGender);
	newCow.cow.gender = inputGender;

	cout << "Was the cow bought or was it born? (Bought/Born): ";
	cin >> answer;

	if (answer == "Bought")
	{
		beenBought = true;
	}

	cout << "Please enter the date of birth, or put Unknown: ";
	cin >> inputBirth;
	newCow.cow.birthDate = inputBirth;

	cout << "Is this cow registered? (Yes/No): ";
	cin >> option;
	if (option == "Yes")
	{
		newCow.registered = true;
		isRegister = true;
	}
	else
	{
		newCow.registered = false;
		isRegister = false;
	}

	int newID = setID(inputBreed, inputGender, isRegister);

	newCow.ID = newID;

	addHelper(newCow);

	if (beenBought == true)
	{
		addToFile("BoughtCow.txt", newCow);
	}
	else
	{
		addToFile("BornCow.txt", newCow);
	}
}


/***************************************************

			Removing from a list

***************************************************/
void CowList::removeFromList(int id, const string& filename)
{
	vector<Cow> tempList;
	bool found = false;

	for (size_t i = 0; i < this->cows.size(); ++i)
	{
		if (this->cows[i].ID == id)
		{
			found = true;
		}
		else
		{
			tempList.push_back(this->cows[i]);
		}
	}

	if (!found)
	{
		cout << "Cow with ID " << id << " not found in the list." << endl;
	}
	else
	{
		this->cows = tempList;

		cout << "Cow with ID " << id << " successfully removed from the list." << endl;
		saveToFile(filename);
	}
}


/***************************************************

	Printers to print the dead and sold lists
	Printer to save file too

***************************************************/
void CowList::printSoldCows() const
{
	CowList soldList("SoldCows.txt");

	soldList.getInfo();
}

void CowList::printDeadCows() const
{
	CowList deadList("DeadCows.txt");

	deadList.bubbleSort();

	deadList.getInfo();

}

void CowList::moveToDeadList(const string& deadFile, int id)
{
	Cow& tempCow = findCowID(id);
	string off;
	tempCow.cow.status = "Dead";
	if (tempCow.registered == true)
	{
		off = "Registered.txt";
	}
	else if (tempCow.registered == false)
	{
		off = "Unregistered.txt";
	}


	addToFile(deadFile, tempCow);
	removeFromList(id, off);
	removeFromList(id, "CowList.txt");
	saveToFile("CowList.txt");
}

void CowList::moveToSoldList(const string& soldFile, int id)
{
	Cow& tempCow = findCowID(id);
	string bye;
	tempCow.cow.sold = true;
	if (tempCow.registered == true)
	{
		bye = "Registered.txt";
	}
	else if (tempCow.registered == false)
	{
		bye = "Unregistered.txt";
	}

	addToFile(soldFile, tempCow);
	removeFromList(id, bye);
	removeFromList(id, "CowList.txt");
	saveToFile("CowList.txt");

}	

void CowList::addToFile(const string& filename, const Cow& newCow)
{
	CowList originalList;

	originalList.loadFromFile(filename);

	originalList.cows.push_back(newCow);
	if (!originalList.cows.empty())
	{
		countSort();
	}

	ofstream outFile(filename);
	if (!outFile.is_open())
	{
		throw fileErrorException();
	}

	originalList.saveToFile(filename);

	outFile.close();
}

void CowList::saveOne(const string& saveFile, const Cow& current)
{
	ofstream outFile(saveFile);

	outFile << "Cow ID: " << current.ID << endl;
	outFile << "Breed: " << current.cow.breed << endl;
	outFile << "Gender: " << current.cow.gender << endl;
	outFile << "Sold = " << (current.cow.sold ? "Yes" : "No") << endl;
	outFile << "Birth: " << current.cow.birthDate << endl;
	outFile << "Status: " << current.cow.status << endl;
	outFile << "Registered: " << (current.registered ? "Yes" : "No") << endl;
	outFile << "***" << endl;

	outFile.close();
}

void CowList::saveToFile(const string& saveFile) const
{
	ofstream outFile(saveFile);
	int count = 0;

	outFile << "***" << endl;

	while (count < cows.size())
	{
		const Cow& current = this->cows[count];

		outFile << "Cow ID: " << current.ID << endl;
		outFile << "Breed: " << current.cow.breed << endl;
		outFile << "Gender: " << current.cow.gender << endl;
		outFile << "Sold = " << (current.cow.sold ? "Yes" : "No") << endl;
		outFile << "Birth: " << current.cow.birthDate << endl;
		outFile << "Status: " << current.cow.status << endl;
		outFile << "Registered: " << (current.registered ? "Yes" : "No") << endl;
		outFile << "***" << endl;

		count++;
	}

	outFile.close();
}

void CowList::loadFromFile(const string& filename)
{
	cows.clear();

	ifstream file(filename);
	if (!file.is_open()) {
		throw fileErrorException();
		return;
	}

	string line;
	const string delimiter = "***";

	while (getline(file, line))
	{
		if (line == delimiter)
		{
			Cow currentCow;
			string key, value;
			int tempId;

			if (!(file >> key >> key >> tempId)) { break; }

			currentCow.ID = tempId;
			file.ignore(numeric_limits<streamsize>::max(), '\n');

			if (!(file >> key)) { break; }
			getline(file, value);
			currentCow.cow.breed = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentCow.cow.gender = value;

			if (!(file >> key >> key)) { break; }
			currentCow.cow.sold = (key == "True");

			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentCow.cow.birthDate = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentCow.cow.status = value;

			if (!(file >> key >> key)) { break; }
			currentCow.registered = (key == "True");

			this->cows.push_back(currentCow);
		}
	}

	file.close();
}
