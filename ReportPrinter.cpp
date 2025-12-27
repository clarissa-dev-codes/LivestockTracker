#include <iostream>
using namespace std;

//all the files excluding errors and driver
#include "Livestock.h"
#include "Chicken.h"
#include "Cow.h"
#include "Goat.h"
#include "Horse.h"
#include "ReportPrinter.h"

ChickenList chickens;
CowList cows;
GoatList goats;
HorseList horses;



//prints all the stuff needed
void Print::AnnualReport()
{
	cout << "************ ANNUAL REPORT ************" << endl;
	ChickenReport();
	CowReport();
	GoatReport();
	HorseReport();
	Location();
	cout << "***************************************" << endl;

}



void Print::GoatReport()
{
	GoatList total("GoatList.txt");
	GoatList boughtGoats("BoughtGoats.txt");
	GoatList bornGoats("BornGoats.txt");
	GoatList soldGoats("SoldGoats.txt");
	GoatList deadGoats("DeadGoats.txt");

	cout << "************ GOAT REPORT ************" << endl;
	cout << " Total Number of Goats: " << total.getHerdSize() << endl;
	cout << " Goats Born This Year: " << bornGoats.getHerdSize() << endl;
	cout << " Goats Bought This Year: " << boughtGoats.getHerdSize() << endl;
	cout << " Goats Sold This Year: " << soldGoats.getHerdSize() << endl;
	cout << " Goats Dead This Year: " << deadGoats.getHerdSize() << endl;
	cout << " *************************************" << endl;
}


void Print::soldGoats()
{
	Goat myGoats;
	cout << "************ SOLD GOATS ************" << endl;
	cout << " Goats that were sold this year: " << endl;
	goats.printsoldGoats();
	cout << " *************************************" << endl;
}

void Print::deadGoats()
{
	cout << "************ DEAD GOATS ************" << endl;	
	cout << " Goats that died this year:  " << endl;
	goats.printdeadGoats();
	cout << " *************************************" << endl;
}



void Print::CowReport()
{
	CowList total("CowList.txt");
	CowList bornCows("BornCow.txt");
	CowList boughtCows("BoughtCow.txt");
	CowList deadCows("DeadCows.txt");
	CowList soldCows("SoldCows.txt");
	CowList registerd("Registered.txt");
	CowList unregistered("Unregistered.txt");

	cout << "************ COW REPORT ************" << endl;
	cout << " Total Number of Cows: " << total.getHerdSize() << endl;
	cout << " Cows Born This Year: " << bornCows.getHerdSize() << endl;
	cout << " Cows Bought This Year: " << boughtCows.getHerdSize() << endl;
	cout << " Cows Sold This Year: " << soldCows.getHerdSize() << endl;
	cout << " Cows Dead This Year: " << deadCows.getHerdSize() << endl;
	cout << " Current Registered Count: " << registerd.getHerdSize() << endl;
	cout << " Current Unregistered Count: " << unregistered.getHerdSize() << endl;
	cout << " *************************************" << endl;
}

void Print::soldCows()
{
	cout << "************ SOLD COWS ************" << endl;
	cout << " Cows that were sold this year:  " << endl;
	cows.printSoldCows();
	cout << " *************************************" << endl;
}
void Print::deadCows()
{
	cout << "************ DEAD COWS ************" << endl;
	cout << " Cows that died this year:  " << endl;
	cows.printDeadCows();
	cout << " *************************************" << endl;
}




void Print::ChickenReport()
{
	ChickenList total("ChickenList.txt");
	ChickenList bornChicks("BornChicken.txt");
	ChickenList boughtChicks("BoughtChicken.txt");
	ChickenList deadChicks("DeadChickens.txt");
	ChickenList soldChicks("SoldChickens.txt");

	cout << "************ CHICKEN REPORT ************" << endl;
	cout << " Total Number of Chickens: " << total.getFlockSize() << endl;
	cout << " Chickens Born This Year: " << bornChicks.getFlockSize() << endl;
	cout << " Chickens Bought This Year: " << boughtChicks.getFlockSize() << endl;
	cout << " Chickens Sold This Year: " << soldChicks.getFlockSize() << endl;
	cout << " Chickens Dead This Year: " << deadChicks.getFlockSize() << endl;
	cout << " *************************************" << endl;
}

void Print::soldChickens()
{
	cout << "************ SOLD CHICKENS ************" << endl;
	cout << " Chickens that were sold this year:  " << endl;
	chickens.printsoldChickens();
	cout << " *************************************" << endl;

}
void Print::deadChickens()
{
	cout << "************ DEAD CHICKENS ************" << endl;
	cout << " Chickens that died this year:  " << endl;
	chickens.printdeadChickens();
	cout << " *************************************" << endl;
}





void Print::HorseReport()
{
	HorseList total("HorseList.txt");
	HorseList bornHorse("BornHorse.txt");
	HorseList boughtHorse("BoughtHorse.txt");
	HorseList soldHorse("SoldHorses.txt");
	HorseList deadHorse("DeadHorses.txt");

	cout << "************ HORSE REPORT ************" << endl;
	cout << " Total Number of Horses: " << total.getHerdSize() << endl;
	cout << " Horses Born This Year: " << bornHorse.getHerdSize() << endl;
	cout << " Horses Bought This Year: " << boughtHorse.getHerdSize() << endl;
	cout << " Horses Sold This Year: " << soldHorse.getHerdSize() << endl;
	cout << " Horses Dead This Year: " << deadHorse.getHerdSize() << endl;
	cout << " *************************************" << endl;
}


void Print::Location()
{
	cout << "************ HORSE LOCATION REPORT ************" << endl;
	cout << "Horses at Mike's Place: " << endl;
	horses.printLocation("MikeHorses.txt");
	cout << "-----------------------------------------------" << endl;
	cout << "Horses in Hackleburg: " << endl;
	horses.printLocation("ALHorses.txt");
	cout << "-----------------------------------------------" << endl;
	cout << "Horses in Mississippi: " << endl;
	horses.printLocation("MSHorses.txt");
	cout << "-----------------------------------------------" << endl;
	cout << "Horses at Jerry's Place: " << endl;
	horses.printLocation("JerryHorses.txt");
	cout << "***********************************************" << endl;
}

void Print::deadHorses()
{
	cout << "************ DEAD HORSES ************" << endl;
	cout << " Horses that died this year:  " << endl;
	horses.printdeadHorses();
	cout << " *************************************" << endl;
}

void Print::soldHorses()
{
	cout << "************ SOLD HORSES ************" << endl;
	cout << " Horses that were sold this year: " << endl;
	horses.printsoldHorses();
	cout << " *************************************" << endl;
}