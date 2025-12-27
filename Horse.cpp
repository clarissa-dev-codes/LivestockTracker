//horse imp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <limits>
#include "Horse.h"
#include "Livestock.h"
/*He only has one breed so everything should start with one
  First number should be 4 for horse


*/

using namespace std;

/***************************************

	Hardcode the file names so there 
	are no typos

***************************************/



string Mikes = "Mike's Place";
string AL = "Hackleburg";
string MS = "Mississippi";
string Jerrys = "Jerry's Place";

int HorseCounter = 000;




void swap(Horse& a,Horse& b)
{
	Horse temp = a;
	a = b;
	b = temp;
}

/********************************************

	Constructors

********************************************/

HorseList::HorseList()
{
	
}

HorseList::HorseList(const string& filename)
{
	ifstream file(filename);
	
	string line;
	const string delimiter = "***";

	while (getline(file, line))
	{
		if (line == delimiter)
		{
			Horse currentHorse;
			string key, value;
			int tempId;
			bool tempSold;

			if (!(file >> key >> key >> tempId)) { break; }

			currentHorse.ID = tempId;
			file.ignore(numeric_limits<streamsize>::max(), '\n');

			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.horse.name = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.horse.breed = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.horse.gender = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.location = value;

			//sold
			if (!(file >> key >> key)) { break; }
			if (key == "True")
			{
				currentHorse.horse.sold = true;
			}
			else
			{
				currentHorse.horse.sold = false;
			}

			//BirthDate
			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentHorse.horse.birthDate = value;

			//status
			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.horse.status = value;



			this->horses.push_back(currentHorse);
		}
	}
	file.close();
}

int HorseList::getHerdSize()
{
	return int(horses.size());
}

int HorseList::setID(string Gender, string Location)
{
	int switchG;
	int	switchL;
	int baseID = 0;

	if (Gender == "Stallion" || "Stud")
	{
		switchG = 1;
	}
	else if (Gender == "Mare")
	{
		switchG = 2;
	}
	else
	{
		switchG = 3;
	}

	if (Location == "Mike's")
	{
		switchL = 1;
	}
	else if (Location == "AL")
	{
		switchL = 2;
	}
	else if (Location == "MS")
	{
		switchL = 3;
	}
	else
	{
		switchL = 4;
	}

	switch (switchG)
	{
	case 1:
	{
		baseID = 4100000 + 10000;
		break;
	}
	case 2:
	{
		baseID = 4100000 + 20000;
		break;
	}
	case 3:
	{
		baseID = 4100000 + 30000;
		break;
	}
	}

	switch (switchL)
	{
	case 1:
	{
		baseID += 1000;
		MikeHerd++;
		break;
	}
	case 2:
	{
		baseID += 2000;
		ALHerd++;
		break;
	}
	case 3:
	{
		baseID += 3000;
		MSHerd++;
		break;
	}
	case 4:
	{
		baseID += 4000;
		JerryHerd++;
		break;
	}
	}

	baseID+= HorseCounter;
	HorseCounter++;

	return baseID;
}

int HorseList::getID(size_t herd) const
{
	if (herd < horses.size())
	{
		return this->horses[herd].ID;
	}

	return -1;
}

void HorseList::getInfo() const
{
	cout << "-------- Herd Info -----------" << endl;
	for (int i = 0; i < horses.size(); ++i)
	{
		const Horse& currentHorse = this->horses[i];
		cout << "Horse ID: " << currentHorse.ID << endl;
		cout << "Horse Name: " << currentHorse.horse.name << endl;
		cout << "Location: " << currentHorse.location << endl;
		cout << "------------------------------" << endl;
	}
}

/********************************************

	Removing from a list

********************************************/
void HorseList::removeFromList(int id, const string& filename)
{
	vector<Horse> tempList;
	bool found = false;

	for (size_t i = 0; i < this->horses.size(); ++i)
	{
		if (this->horses[i].ID == id)
		{
			found = true;
		}
		else
		{
			tempList.push_back(this->horses[i]);
		}
	}

	if (!found)
	{
		cout << "Horse with ID " << id << " not found in the list" << endl;
	}
	else
	{
		this->horses = tempList;
		cout << "Horse with ID " << id << " successfully removed from list." << endl;
		saveToFile(filename);
	}
}

/********************************************

	Quick Sort Function and helpers

********************************************/
void quickSort(vector<Horse> toSort, int low, int high) 
{
	if (low < high)
	{
		int pivot = toSort[high].ID;

		int x = (low - 1);

		for (int y = low; y < high; y++)
		{
			x++;
			swap(toSort[x], toSort[y]);
		}

		swap(toSort[x + 1], toSort[high]);
		int partIndex = x + 1;

		quickSort(toSort, low, partIndex - 1);
		quickSort(toSort, partIndex + 1, high);
	}

}

void HorseList::addHelper(const Horse& newHorse)
{
	this->horses.push_back(newHorse);

	if (!this->horses.empty())
	{
		quickSort(this->horses, 0, this->horses.size() - 1);
	}
}	

/********************************************

		Adding new Horses

********************************************/
void HorseList::addNewHorse()
{
	Horse newHorse;
	string inputName;
	string inputGender;
	string inputBreed;
	string inputOther;
	string inputLocation;
	string option;
	bool beenBought = false;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Please enter the name of the new horse: ";
	getline(cin, inputName);
	newHorse.horse.name = inputName;

	cout << "Please enter the gender of the new horse (Stallion/Mare/Gelding): ";
	getline(cin, inputGender);
	newHorse.horse.gender = inputGender;

	cout << "Please enter the location of the new horse (Mike's/AL/MS/Jerry's): ";
	getline(cin, inputLocation);
	newHorse.location = inputLocation;

	cout << "Was the horse bought or born? ";
	cin >> inputOther;
	if (inputOther == "Bought")
	{
		beenBought = true;
		cout << "Do you know the birth date of the horse? (Yes/No)" << endl;
		cin >> option;
		if (option == "Yes")
		{
			cout << "Please enter the birth date: ";
			cin >> newHorse.horse.birthDate;
		}
		else
		{
			newHorse.horse.birthDate = "Unknown";
		}
	}
	else
	{
		cout << "Please enter date of birth: ";
		cin >> newHorse.horse.birthDate;
	}

	int newID = setID(inputGender, inputLocation);

	newHorse.ID = newID;

	addHelper(newHorse);

	if (beenBought == true)
	{
		addToFile("BoughtHorse.txt", newHorse);
	}
	else
	{
		addToFile("BornHorse.txt", newHorse);
	}

}



/***************************************************
* 
	Printers to print the dead and sold lists

***************************************************/
void HorseList::printsoldHorses() const
{
	HorseList soldList("SoldHorses.txt");

	soldList.getInfo();
}

void HorseList::printdeadHorses() const
{
	HorseList deadList("DeadHorses.txt");

	deadList.getInfo();
}

/*********************************************

		Sort Method

**********************************************/
Horse& HorseList::findHorseID(int searchID)
{
	int low = 0;
	size_t high = horses.size() - 1;

	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (horses[mid].ID == searchID)
		{
			return horses[mid];
		}
		else if (horses[mid].ID > searchID)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
}

/********************************************

	loading in from a file

********************************************/
void HorseList::loadFromFile(const string& filename)
{
	ifstream file(filename);

	string line;
	const string delimiter = "***";

	while (getline(file, line))
	{
		if (line == delimiter)
		{
			Horse currentHorse;
			string key, value;
			int tempId;
			bool tempSold;

			if (!(file >> key >> key >> tempId)) { break; }

			currentHorse.ID = tempId;
			file.ignore(numeric_limits<streamsize>::max(), '\n');

			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.horse.name = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.horse.breed = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.horse.gender = value;

			//sold
			if (!(file >> key >> key)) { break; }
			if (key == "True")
			{
				currentHorse.horse.sold = true;
			}
			else
			{
				currentHorse.horse.sold = false;
			}

			//BirthDate
			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentHorse.horse.birthDate = value;

			//status
			if (!(file >> key)) { break; }
			getline(file, value);
			currentHorse.horse.status = value;



			this->horses.push_back(currentHorse);
		}
	}
	file.close();
}


/********************************************

	Moving Horses from one location to another

********************************************/
void HorseList::moveLocation(const string& locationFile, int id, string newLocation)
{
	Horse& tempHorse = findHorseID(id);

	tempHorse.location = newLocation;
	addToFile(newLocation, tempHorse);
	removeFromList(id, locationFile);
	saveToFile(locationFile);
}

/********************************************* 

		Print Herd in that location

********************************************/
void HorseList::printLocation(const string& locationFile) const
{
	
	string Place;
	if (locationFile == "MikeHorses.txt")
	{
		Place = Mikes;

	}
	else if (locationFile == "ALHorses.txt")
	{
		Place = AL;

	}
	else if (locationFile == "MSHorses.txt")
	{
		Place = MS;
	}
	else if (locationFile == "JerryHorses.txt")
	{
		Place = Jerrys;
	}
	else
	{
		Place = "Unknown Filename";
	}

	HorseList locationList(locationFile);
	

	cout << "--------" << Place << " Info---------- - " << endl;
	locationList.getInfo();
}	
/**********************************************

	addToFile

**********************************************/
void HorseList::addToFile(const string& filename, const Horse& horsePtr)
{
	HorseList originalList;

	originalList.loadFromFile(filename);
	originalList.horses.push_back(horsePtr);

	if (!originalList.horses.empty())
	{
		quickSort(originalList.horses, 0, originalList.horses.size() - 1);
	}

	ofstream outFile(filename);
	if (!outFile.is_open())
	{
		throw fileErrorException();
	}

	originalList.saveToFile(filename);

	outFile.close();
}


/**********************************************

	Moving things to new lists (Sold/Dead)

**********************************************/
void HorseList::moveToDeadList(const string& deadFile, int id)
{
	string location;
	Horse& tempHorse = findHorseID(id);
	tempHorse.horse.status = "Dead";
	string place = tempHorse.location;

	if (place == "Mike's")
	{
		location = "MikeHorses.txt";
	}
	else if (place == "AL")
	{
		location = "ALHorses.txt";
	}
	else if (place == "MS")
	{
		location = "MSHorses.txt";
	}
	else if (place == "Jerry's")
	{
		location = "JerryHorses.txt";
	}


	addToFile(deadFile, tempHorse);
	removeFromList(id, "HorseList.txt");
	removeFromList(id, location);
	saveToFile("HorseList.txt");
}

void HorseList::moveToSoldList(const string& soldFile, int id)
{
	string location;
	
	Horse& tempHorse = findHorseID(id);
	tempHorse.horse.sold = true;
	string place = tempHorse.location;

	if (place == "Mike's")
	{
		location = "MikeHorses.txt";
	}
	else if (place == "AL")
	{
		location = "ALHorses.txt";
	}
	else if (place == "MS")
	{
		location = "MSHorses.txt";
	}
	else if (place == "Jerry's")
	{
		location = "JerryHorses.txt";
	}

	addToFile(soldFile, tempHorse);
	removeFromList(id, "HorseList.txt");
	removeFromList(id, location);
	saveToFile("HorseList.txt");
}


/********************************************

			Save to File and
			Save one to file

********************************************/
void HorseList::saveOne(const string& saveFile, const Horse& currentHorse)
{
	ofstream outFile(saveFile);

	outFile << "Horse ID: " << currentHorse.ID << endl;
	outFile << "Name: " << currentHorse.horse.name << endl;
	outFile << "Breed: " << currentHorse.horse.breed << endl;
	outFile << "Gender: " << currentHorse.horse.gender << endl;
	outFile << "Location: " << currentHorse.location << endl;
	outFile << "Sold = " << (currentHorse.horse.sold ? "True" : "False") << endl;
	outFile << "Birth" << currentHorse.horse.birthDate << endl;
	outFile << "Status: " << currentHorse.horse.status << endl;
	outFile << "***" << endl;

	outFile.close();
}

void HorseList::saveToFile(const string& saveFile) const
{
	ofstream outFile(saveFile);
	int count = 0;

	outFile << "***" << endl;

	while (count < horses.size())
	{
		const Horse& currentHorse = this->horses[count];

		outFile << "Horse ID:" << currentHorse.ID << endl;
		outFile << "Name:" << currentHorse.horse.name << endl;
		outFile << "Breed:" << currentHorse.horse.breed << endl;
		outFile << "Gender:" << currentHorse.horse.gender << endl;
		outFile << "Location:" << currentHorse.location << endl;
		outFile << "Sold = " << (currentHorse.horse.sold ? "True" : "False") << endl;
		outFile << "Birth" << currentHorse.horse.birthDate << endl;
		outFile << "Status:" << currentHorse.horse.status << endl;
		outFile << "***" << endl;
		count++;
	}
}