//goat imp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <limits>
#include "Goat.h"
#include "Livestock.h"

using namespace std;

/*  Notes for IDs   
*   - Just kidding, the first number should be 3 and then the rest below 
* 
	First three numbers have meaning

	- First is the breed
	- Second is the Gender
	- Third is if the goat was bought or born

	the last three are just a counter
*/

//open the file if there is any




int Goatcounter = 000;

void swap(Goat& a,Goat& b)
{
	Goat temp = a;
	a = b;
	b = temp;
}




GoatList::GoatList()
{
	
}


GoatList::GoatList(const string& filename)
{
	ifstream file(filename);
	
	string line;
	const string delimiter = "***";

	while (getline(file, line)) // Read file line by line
	{
		

		if (line == delimiter)
		{
			

			Goat currentGoat;
			string key, value;
			int tempId;
			bool tempSold;

			
			if (!(file >> key >> key >> tempId)) { break; }
			
			currentGoat.goatID = tempId;
			file.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline

			
			if (!(file >> key)) {  break; }
			getline(file, value);
			currentGoat.goat.name = value;

			
			if (!(file >> key)) { break; }
			getline(file, value);
			currentGoat.goat.breed = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentGoat.goat.gender = value;

			//sold
			if (!(file >> key >> key)) { break; }
			if (key == "True")
			{
				currentGoat.goat.sold = true;
			}
			else
			{
				currentGoat.goat.sold = false;
			}

			//BirthDate
			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentGoat.goat.birthDate = value;

			//status
			if (!(file >> key)) { break; }
			getline(file, value);
			currentGoat.goat.status = value;


			
			this->goats.push_back(currentGoat);
		}
	}
	file.close();
}

/************************************


	       Count Management


*************************************/


int GoatList::getHerdSize()
{
	return int(goats.size());
}


int GoatList::setGoatID(string breed, string gender, string other)
{
	
	int baseID = 0; 
	int switchB, switchG, switchO;

	if (breed == "Nigerian Dwarf")
	{
		switchB = 1;
	}
	else if (breed == "Nigerian")
	{
		switchB = 2;
	}
	else
	{
		switchB = 3;
	}

	if (gender == "Billy")
	{
		switchG = 1;
	}
	else if (gender == "Nanny")
	{
		switchG = 2;
	}
	else
	{
		switchG = 3;
	}

	
	if (other == "Bought")
	{
		switchO = 1;
	}
	else
	{
		switchO = 2;
	}

	
	switch (switchB)
	{
	case 1:
		baseID = 3100000; 
		break;
	case 2:
		baseID = 3200000; 
		break;
	case 3:
		baseID = 3300000; 
		break;
	default:
		throw runtime_error("Invalid breed option during ID generation.");
	}

	switch (switchG)
	{
	case 1:
		baseID += 10000; 
		break;
	case 2:
		baseID += 20000; 
		break;
	case 3:
		baseID += 30000; 
		break;
	}
	switch (switchO)
	{
	case 1:
		baseID += 1000; 
		break;
	case 2:
		baseID += 2000; 
		break;
	}

	
	baseID += Goatcounter;
	Goatcounter++; 

	return baseID;
}
int GoatList::getGoatID(size_t herd) const
{
	if (herd < goats.size())
	{
		return this->goats[herd].goatID;
	}

	return -1;

}

void GoatList::getInfo() const
{
	cout << "-------- Herd Info -----------" << endl;
	for (int i = 0; i < goats.size(); ++i)
	{
		const Goat& currentGoat = this->goats[i];
		cout << "Goat ID: " << currentGoat.goatID << endl;
		cout << "Goat name: " << currentGoat.goat.name << endl;
		cout << "------------------------------" << endl;
	}
}

/*----------------------------------------------------
			  Removing from a list
----------------------------------------------------*/

void GoatList::removeFromList(int id)
{
	vector<Goat> tempList;
	bool found = false;

	for (size_t i = 0; i < this->goats.size(); ++i)
	{
		if (this->goats[i].goatID == id)
		{
			found = true;
		}
		else
		{
			tempList.push_back(this->goats[i]);
		}
	}

	if (!found)
	{
		cout << "Goat with ID " << id << " not found in the list" << endl;
	}
	else
	{
		this->goats = tempList;

		cout << "Goat with ID " << id << " successfully removed from list." << endl;
		saveToFile("GoatList.txt");
	}
}

/*-----------------------------------------------------
			Quick Sort Function
-----------------------------------------------------*/
void quickSort(vector<Goat> toSort, int low, int high)
{
	if (low < high)
	{
		int pivot = toSort[high].goatID;

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

/*--------------------------------------------------
			Add helper
--------------------------------------------------*/
void GoatList::addHelper(const Goat& newGoat)
{
	this->goats.push_back(newGoat);

	if (!this->goats.empty())
	{
		quickSort(this->goats, 0, this->goats.size() - 1);
	}
}

/*----------------------------------------------------
	
				Adding new Goats
	
----------------------------------------------------*/
void GoatList::addNewGoat()
{
	Goat newGoat;
	string inputName;
	string inputGender;
	string inputBreed;
	string inputOther;
	string option;
	bool beenBought = false;

	//ask about name
	cout << "Please enter the name of the new goat: ";
	cin >> inputName;
	newGoat.goat.name = inputName;

	//ask about breed
	cout << "Please enter the breed of the new goat (Nigerian Dwarf/Nigerian/Other): ";
	cin >> inputBreed;
	newGoat.goat.breed = inputBreed;

	//ask about gender
	cout << "Please enter the gender of the new goat (Billy/Nanny/Wether): ";
	cin >> inputGender;
	newGoat.goat.gender = inputGender;


	//ask about bought/born
	cout << "Was the goat bought or born? ";
	cin >> inputOther;
	if (inputOther == "Bought")
	{
		beenBought = true;
		cout << "Do you know the birth date of the goat? (Yes/No)" << endl;
		cin >> option;
		if (option == "Yes")
		{
			cout << "Please enter the birth date: ";
			cin >> newGoat.goat.birthDate;
		}
		else
		{
			newGoat.goat.birthDate = "Unknown";
		}
	}
	else
	{
		
		
		cout << "Please enter date of birth: ";
		cin >> newGoat.goat.birthDate;
	}

	//call ID method
	int newID = setGoatID(inputBreed, inputGender, inputOther);

	newGoat.goatID = newID;

	//add the new goat to the list
	addHelper(newGoat);

	
	if (beenBought == true)
	{
		addToFile("BoughtGoats.txt", newGoat);
	}
	else
	{
		addToFile("BornGoats.txt", newGoat);
	}
	

}

/***************************************************

	Printers to print the dead and sold lists

***************************************************/
void GoatList::printsoldGoats() const
{
	GoatList soldLIst("SoldGoats.txt");

	soldLIst.getInfo();
}

void GoatList::printdeadGoats() const
{
	GoatList deadList("DeadGoats.txt");

	deadList.getInfo();
}
/*-------------------------------------------------

			find the ID
	
-------------------------------------------------*/
Goat& GoatList::findGoatID(int searchID)
{
	int low = 0;
	size_t high = goats.size() - 1;

	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (goats[mid].goatID == searchID)
		{
			return goats[mid];
		}
		else if (goats[mid].goatID > searchID)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}

	
}


/*----------------------------------------------------

	Moving things to new lists (Sold/Dead)

----------------------------------------------------*/
void GoatList::loadFromFile(const string& filename)
{
	ifstream file(filename);
	
	string line;
	const string delimiter = "***";

	while (getline(file, line)) // Read file line by line
	{


		if (line == delimiter)
		{


			Goat currentGoat;
			string key, value;
			int tempId;
			bool tempSold;


			if (!(file >> key >> key >> tempId)) { break; }

			currentGoat.goatID = tempId;
			file.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline


			if (!(file >> key)) { break; }
			getline(file, value);
			currentGoat.goat.name = value;


			if (!(file >> key)) { break; }
			getline(file, value);
			currentGoat.goat.breed = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentGoat.goat.gender = value;

			//sold
			if (!(file >> key >> key)) { break; }
			if (key == "True")
			{
				currentGoat.goat.sold = true;
			}
			else
			{
				currentGoat.goat.sold = false;
			}

			//BirthDate
			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentGoat.goat.birthDate = value;

			//status
			if (!(file >> key)) { break; }
			getline(file, value);
			currentGoat.goat.status = value;



			this->goats.push_back(currentGoat);
		}
	}
	file.close();
}

void GoatList::addToFile(const string& filename, const Goat& goatPtr)
{
	GoatList originalList;

	originalList.loadFromFile(filename);

	originalList.goats.push_back(goatPtr);

	if (!originalList.goats.empty())
	{
		quickSort(originalList.goats, 0, originalList.goats.size() - 1);
	}

	ofstream outFile(filename);
	if (!outFile.is_open()) 
	{
		throw fileErrorException();
	}
	
	
	
	originalList.saveToFile(filename);

	outFile.close();
	
}

void GoatList::moveToDeadList(const string& deadFile, int id)
{
	Goat& tempGoat = findGoatID(id);

	tempGoat.goat.status = "Dead";

	addToFile(deadFile, tempGoat);
	removeFromList(id);
	saveToFile("GoatList.txt");
}

void GoatList::moveToSoldList(const string& soldFile, int id)
{
	Goat& tempGoat = findGoatID(id);

	tempGoat.goat.sold = true;

	addToFile(soldFile, tempGoat);
	removeFromList(id);
	saveToFile("GoatList.txt");

}

void GoatList::saveOne(const string& saveFile, const Goat& goats)
{
	ofstream outFile(saveFile);

	outFile << "Goat ID:" << goats.goatID << endl;
	outFile << "Name:" << goats.goat.name << endl;
	outFile << "Breed:" << goats.goat.breed << endl;
	outFile << "Gender:" << goats.goat.gender << endl;
	outFile << "Sold = " << (goats.goat.sold ? "True" : "False") << endl;
	outFile << "Birth" << goats.goat.birthDate << endl;
	outFile << "Status:" << goats.goat.status << endl;
	outFile << "***" << endl; //separator between animals

	outFile.close();
}

void GoatList::saveToFile(const string& saveFile)
{
	ofstream outFile(saveFile);
	int count = 0;

	outFile << "***" << endl;

	while (count < goats.size())
	{
		const Goat& currentGoat = this->goats[count];

		outFile << "Goat ID: " << currentGoat.goatID << endl;
		outFile << "Name: " << currentGoat.goat.name << endl;
		outFile << "Breed: " << currentGoat.goat.breed << endl;
		outFile << "Gender" << currentGoat.goat.gender << endl;
		outFile << "Sold = " << (currentGoat.goat.sold ? "True" : "False") << endl;
		outFile << "Birth" << currentGoat.goat.birthDate << endl;
		outFile << "Status: " << currentGoat.goat.status << endl;
		outFile << "***" << endl; //separator between animals
		count++;
	}

	outFile.close();
}



