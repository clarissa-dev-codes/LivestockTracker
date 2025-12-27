//chicken imp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <limits>

#include "Livestock.h"
#include "Chicken.h"

using namespace std;

/* Chicken ID notes
* First number should be 1 for chicken
* 
* Breed: (xxx,xxx)
*	1 - Rhode Island Reds
*   2 - Smokey Pearls
*   3 - Foghorn Leghorn
*	4 - Black Sexlings
*   5 - Buff Orpingtons
* 
* Gender: (xx,xxx)
*	1 - Hen
*	2 - Rooster
* 
* Color Band: (x,xxx)
*	1 - Purple
*   2 - Green
*   3 - Yellow
*   4 - Red              */




int ChickCounter = 000; //have the counter count how many items get added in from the save file if there is stuff in the file
					// have the counter be 000 if the svae file is empty

ChickenList::ChickenList()
{
	
}

ChickenList::ChickenList(const string& filename)
{
	ifstream file(filename);

	string line;
	const string delimiter = "***";
 
  

	while (getline(file, line))
	{

		if (line == delimiter)
		{
      
			Chicken currentChick;
			string key, value;
			int tempId;
			bool tempSold;


			if (!(file >> key >> key >> tempId)) { break; }

			currentChick.coopID = tempId;
			file.ignore(numeric_limits<streamsize>::max(), '\n');
      

			if (!(file >> key)) { break; }
			getline(file, value);
			currentChick.chicken.name = value;


			if (!(file >> key)) { break; }
			getline(file, value);
			currentChick.chicken.breed = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentChick.chicken.gender = value;

			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentChick.colorBand = value;

			//sold
			if (!(file >> key >> key)) { break; }
			if (key == "True")
			{
				currentChick.chicken.sold = true;
			}
			else
			{
				currentChick.chicken.sold = false;
			}

			//BirthDate
			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentChick.chicken.birthDate = value;

			//status
			if (!(file >> key)) { break; }
			getline(file, value);
			currentChick.chicken.status = value;

			this->chick.push_back(currentChick);
		}
	}
	file.close();

}


int ChickenList::getFlockSize()
{
	return int(chick.size());
}


int ChickenList::getCoopID(size_t flock) const
{
	if (flock < chick.size())
	{
		return this->chick[flock].coopID;
	}

	return -1;
}


int ChickenList::setCoopID(string breed, string gender, string colorBand)
{
	int switchB;
	int switchG;
	int switchC;
	int baseID = 0;

	if (breed == "Rhode Island Red")
	{
		switchB = 1;
	}
	else if (breed == "Smokey Pearls")
	{
		switchB = 2;
	}
	else if (breed == "Foghorn Leghorn")
	{
		switchB = 3;
	}
	else if (breed == "Black Sexlings")
	{
		switchB = 4;
	}
	else
	{
		switchB = 5;
	}

	if (gender == "Hen")
	{
		switchG = 1;
	}
	else
	{
		switchG = 2;
	}

	if (colorBand == "Purple")
	{
		switchC = 1;
	}
	else if (colorBand == "Green")
	{
		switchC = 2;
	}
	else if (colorBand == "Yellow")
	{
		switchC = 3;
	}
	else
	{
		switchC = 4;
	}
	//breed
	switch (switchB)
	{
	case 1:
	{
		baseID = 1100000;
		break;
	}
	case 2:
	{
		baseID = 1200000;
		break;
	}
	case 3:
	{
		baseID = 1300000;
		break;
	}
	case 4:
	{
		baseID = 1400000;
		break;
	}
	case 5:
	{
		baseID = 1500000;
		break;
	}
	}

	//gender

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

	//color band
	switch (switchC)
	{
	case 1:
	{
		baseID += 1000;
		break;
	}
	case 2:
	{
		baseID += 2000;
		break;
	}
	case 3:
	{
		baseID += 3000;
		break;
	}
	case 4:
	{
		baseID += 4000;
		break;
	}

	}

	//adding the counter at the end
	baseID += ChickCounter;
	ChickCounter++;

	return baseID;
}
/*********************************************

		Find Chicken ID

*********************************************/
Chicken& ChickenList::findChickenID(int searchID)
{
	int low = 0;
	size_t high = chick.size() - 1;

	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (chick[mid].coopID == searchID)
		{
			return chick[mid];
		}
		else if (chick[mid].coopID > searchID)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
}


/*********************************************

		Sort method

*********************************************/
void quickSort(vector<Chicken> toSort, int low, int high)
{
	if (low < high)
	{
		int pivot = toSort[high].coopID;

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


/**********************************************

		Adding a new Chicken and helper
	
**********************************************/
void ChickenList::addNewChicken()
{
	Chicken newChicken;
	string inputName;
	string inputBreed;
	string inputGender;
	string inputColorBand;
	string inputOther;
	string option;
	bool beenBought = false;


	cin.ignore(numeric_limits<streamsize>::max(), '\n');
 
 
	//ask about name
	cout << "Please enter the name of the new chicken: ";
	getline(cin, inputName);
	newChicken.chicken.name = inputName;

	//ask about breed
	cout << "Please enter the breed of the new chicken (Rhode Island Red/Smokey Pearls/Foghorn Leghorn/Black Sexlings/Buff Orpingtons): ";
	getline(cin, inputBreed);
	newChicken.chicken.breed = inputBreed;

	//ask about gender
	cout << "Please enter the gender of the new chicken (Rooster/Hen): ";
	getline(cin, inputGender);
	newChicken.chicken.gender = inputGender;

	//ask about color bands
	cout << "Please enter the color band of the new chicken (Purple/Green/Yellow/Red): ";
	getline(cin, inputColorBand);
	newChicken.colorBand = inputColorBand;

	//ask about bought/born
	cout << "Was the chicken bought or born? ";
	cin >> inputOther;
	if (inputOther == "Bought")
	{
		beenBought = true;
		cout << "Do you know the birth date of the chicken? (Yes/No): " << endl;
		cin >> option;
		if (option == "Yes")
		{
			cout << "Please enter the birth date: ";
			cin >> newChicken.chicken.birthDate;
		}
		else
		{
			newChicken.chicken.birthDate = "Unknown";
		}
	}
	else
	{
		cout << "Please enter date of birth: ";
		cin >> newChicken.chicken.birthDate;
	}

	//call ID method
	int newID = setCoopID(inputBreed, inputGender, inputColorBand);

	newChicken.coopID = newID;

	//add the new chicken to the list
	addHelper(newChicken);

	if (beenBought == true)
	{
		addToFile("BoughtChicken.txt", newChicken);
	}
	else
	{
		addToFile("BornChicken.txt", newChicken);
	}
	
}

void ChickenList::addHelper(const Chicken& newChicken)
{
	this->chick.push_back(newChicken);

	if (!this->chick.empty())
	{
		quickSort(this->chick, 0, this->chick.size() - 1);
	}
}

void ChickenList::addToFile(const string& filename, const Chicken& chick)
{
	ChickenList originalList;

	originalList.loadFromFile(filename);

	originalList.chick.push_back(chick);

	if (!originalList.chick.empty())
	{
		quickSort(originalList.chick, 0, originalList.chick.size() - 1);
	}

	ofstream outFile(filename);
	if (!outFile.is_open())
	{
		throw fileErrorException();
	}

	originalList.saveToFile(filename);
	outFile.close();
}

/***************************************************

	Get Info to override

***************************************************/
void ChickenList::getInfo() const
{
	cout << "----------- Flock Info -----------" << endl;
	for (int i = 0; i < chick.size(); ++i)
	{
		const Chicken& currentChick = this->chick[i];
		cout << "Name: " << currentChick.chicken.name << endl;
		cout << "Breed: " << currentChick.chicken.breed << endl;
		cout << "Color Band: " << currentChick.colorBand << endl;
		cout << "--------------------------------------" << endl;
	}
}


/**********************************************

		Load From a file

**********************************************/
void ChickenList::loadFromFile(const string& filename)
{
	ifstream file(filename);

	string line;
	const string delimiter = "***";

	while (getline(file, line))
	{
		if (line == delimiter)
		{
			Chicken currentChick;
			string key, value;
			int tempId;
			bool tempSold;

			if (!(file >> key >> key >> tempId)) { break; }

			currentChick.coopID = tempId;
			file.ignore(numeric_limits<streamsize>::max(), '\n');

			if (!(file >> key)) { break; }
			getline(file, value);
			currentChick.chicken.name = value;


			if (!(file >> key)) { break; }
			getline(file, value);
			currentChick.chicken.breed = value;

			if (!(file >> key)) { break; }
			getline(file, value);
			currentChick.chicken.gender = value;

			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentChick.colorBand = value;

			//sold
			if (!(file >> key >> key)) { break; }
			if (key == "True")
			{
				currentChick.chicken.sold = true;
			}
			else
			{
				currentChick.chicken.sold = false;
			}

			//BirthDate
			if (!(file >> key >> key)) { break; }
			getline(file, value);
			currentChick.chicken.birthDate = value;

			//status
			if (!(file >> key)) { break; }
			getline(file, value);
			currentChick.chicken.status = value;

			this->chick.push_back(currentChick);
		}
	}
	file.close();
}

/***************************************************

	Printers to print the dead and sold lists
	Printer to save file too

***************************************************/
void ChickenList::printsoldChickens() const
{
	
	ChickenList soldList("SoldChickens.txt");
	soldList.getInfo();
}

void ChickenList::printdeadChickens() const
{
	ChickenList deadList("DeadChickens.txt");
	deadList.getInfo();
}

//save to files
void ChickenList::saveToFile(const string& saveFile) const
{
	ofstream outFile(saveFile);
	int count = 0;

	outFile << "***" << endl;

	while (count < chick.size())
	{
		const Chicken& currentChick = this->chick[count];

		outFile << "Chicken ID:" << currentChick.coopID << endl;
		outFile << "Name:" << currentChick.chicken.name << endl;
		outFile << "Breed:" << currentChick.chicken.breed << endl;
		outFile << "Gender:" << currentChick.chicken.gender << endl;
		outFile << "Color Band:" << currentChick.colorBand << endl;
		outFile << "Sold =" << (currentChick.chicken.sold ? "Yes" : "No") << endl;
		outFile << "Birth" << currentChick.chicken.birthDate << endl;
		outFile << "Status:" << currentChick.chicken.status << endl;
		outFile << "***" << endl;
		count++;
	}
}

void ChickenList::saveOne(const string& saveFile, const Chicken& currentChick)
{
	ofstream outFile(saveFile);

	outFile << "Chicken ID: " << currentChick.coopID << endl;
	outFile << "Name:" << currentChick.chicken.name << endl;
	outFile << "Breed:" << currentChick.chicken.breed << endl;
	outFile << "Gender:" << currentChick.chicken.gender << endl;
	outFile << "Color Band:" << currentChick.colorBand << endl;
	outFile << "Sold =" << (currentChick.chicken.sold ? "Yes" : "No") << endl;
	outFile << "BirthDate =" << currentChick.chicken.birthDate << endl;
	outFile << "Status: " << currentChick.chicken.status << endl;
	outFile << "***" << endl;

	outFile.close();
}

