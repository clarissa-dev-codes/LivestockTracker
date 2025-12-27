//herd manager (driver)
#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

#include "Livestock.h"
#include "Chicken.h"
#include "Cow.h"
#include "Goat.h"
#include "Horse.h"
#include "ReportPrinter.h"
/*------------------------------------------
  text files names:
  - the sold list "Sold List.txt"
  - the dead list "Dead List.txt"
  - breeding report list "Breeding Record.txt"
-------------------------------------------*/

int choice;
char option;
char option2;


/*-------------------------------------------

		To Clear the Screen and pause

--------------------------------------------*/
void clearScreen()
{
	
#ifdef _WIN32
	system("cls"); 
#else
	
	system("clear");
#endif
}

//a nifty little method I found so that the user can read the reports at their 
//leisure before continuing
void pause_program()
{
    cout << "Press ENTER to continue..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


/*-------------------------------------------

		Object Instances that I need

--------------------------------------------*/

Print printer;
ChickenList chickenList;
CowList cowList;	
GoatList goatList;	
HorseList horseList;



string goatListName = "GoatList.txt"; //made
string horseListName = "HorseList.txt"; //made
string chickListName = "ChickenList.txt"; //made
string cowListName = "CowList.txt"; //made

string soldGoats = "SoldGoats.txt"; //made
string deadGoats = "DeadGoats.txt"; //made

string soldHorses = "SoldHorses.txt"; //made
string deadHorses = "DeadHorses.txt"; //made

string soldChicks = "SoldChickens.txt"; //made
string deadChicks = "DeadChickens.txt"; //made

string regCows = "Registered.txt"; //made
string unregCows = "Unregistered.txt"; //made
string soldCows = "SoldCows.txt"; //made
string deadCows = "DeadCows.txt"; //made

string Mike = "MikeHorses.txt"; //made
string Hack = "ALHorses.txt"; //made
string Miss = "MSHorses.txt"; //made
string Jerry = "JerryHorses.txt"; //made


/*----------------------------------------------------
	Animal Menu just so I don't have to keep writing it
----------------------------------------------------*/

void AnimalMenu()
{
	cout << "Which Animals would you like to see?" << endl;
	cout << "---------------------------------" << endl;
	cout << "1) Chicken" << endl;
	cout << "2) Cow" << endl;
	cout << "3) Goat" << endl;
	cout << "4) Horse" << endl;
	cout << "5) Horse Locations" << endl;
	cout << "6) Full Annual Report" << endl;
	cout << "7) Exit Program" << endl;
	cout << "---------------------------------" << endl;
}

/*----------------------------------------------------
	Everything else that I need (For each animal)
----------------------------------------------------*/
void MainMenu()
{
	cout << "Please select an option from the menu below: " << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "1) Manage Animals" << endl;
	cout << "2) See Sold Animals List" << endl;
	cout << "3) See Dead Animals List" << endl;
	cout << "4) Annual Report" << endl;
	cout << "5) Back" << endl;
	cout << "-----------------------------------------------" << endl;
}

void ManageAnimalsMenu()
{
	cout << "Please select an option from the menu below: " << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "1) Add Animal" << endl;
	cout << "2) Move to Sold List" << endl;
	cout << "3) Move to Dead List" << endl;
	cout << "4) Back" << endl;
	cout << "-----------------------------------------------" << endl;
}

/*------------------------------------------------------------
			Notes:
	- Mangage animals should let you add animals
	- Move to sold should move the animal to the sold list
	- Move to dead should move the animal to the dead list
	- Report is kinda obvious
-------------------------------------------------------------*/


int main()
{
    clearScreen();
    cout << "Welcome! " << endl;
    char animalOption = '0'; // Corresponds to option in AnimalMenu

    // --- Main Program Loop (Animal Menu Level) ---
    // Loops until user enters '7' to exit the entire program
    while (animalOption != '7')
    {
        AnimalMenu(); // Displays options 1-7
        cin >> animalOption;

        if (animalOption == '7') 
        {
            cout << "Exiting program. Have a nice day!" << endl;
            break;
        }

        clearScreen(); // Clear screen after selecting an animal/report

        switch (animalOption)
        {
        case '1': // Chicken
        case '2': // Cow
        case '3': // Goat
        case '4': // Horse
        {
            char mainOption = '0'; // Corresponds to option in MainMenu (Back is '5')

            
            if (animalOption == '1')
            {
                chickenList.loadFromFile(chickListName);
            }
            if (animalOption == '2')
            {
                cowList.loadFromFile(cowListName);
            }
            if (animalOption == '3')
            {
                goatList.loadFromFile(goatListName);
            }
            if (animalOption == '4')
            {
                horseList.loadFromFile(horseListName);
            }

            // --- Main Menu Loop (Manage, Sold, Dead, Report, Back) ---
            while (mainOption != '5')
            {
                MainMenu(); // Displays options 1-5
                cin >> mainOption;

                if (mainOption == '5') 
                {
                    clearScreen(); 
                    break;         
                }

                clearScreen(); // Clear screen after selecting main menu choice

                switch (mainOption)
                {
                case '1': // Manage Animals Menu (Add, Move Sold/Dead, Back)
                {
                    char manageOption = '0';
                    while (manageOption != '4')
                    {
                        ManageAnimalsMenu(); 
                        cin >> manageOption;

                        if (manageOption == '4') 
                        {
                            clearScreen(); // Clear screen before returning to MainMenu
                            break;         
                        }

                        

                        if (animalOption == '1') //chicken
                        {
                            if (manageOption == '1')
                            {
                                chickenList.addNewChicken();
                                chickenList.saveToFile(chickListName);
                            }
                            else if (manageOption == '2')
                            {
                                int chickID;
                                chickenList.getInfo();
                                cout << "Enter ID to move to sold: ";
                                cin >> chickID;
                                goatList.moveToSoldList(soldChicks, chickID);

                            }
                            else if (manageOption == '3')
                            {
                                int chickID;
                                chickenList.getInfo();
                                cout << "Enter ID to move to dead: ";
                                cin >> chickID;
                                goatList.moveToDeadList(deadChicks, chickID);
                            }
                            break;
                        }
                        else if (animalOption == '2') //cow
                        {
                            if (manageOption == '1')
                            {
                                cowList.addNewCow();
                                cowList.saveToFile(cowListName);
                            }
                            else if (manageOption == '2')
                            {
                                int cowID;
                                cowList.getInfo();
                                cout << "Enter ID to move to sold: ";
                                cin >> cowID;
                                cowList.moveToSoldList(soldCows, cowID);

                            }
                            else if (manageOption == '3')
                            {
                                int cowID;
                                cowList.getInfo();
                                cout << "Enter ID to move to sold: ";
                                cin >> cowID;
                                cowList.moveToDeadList(deadCows, cowID);
                            }
                            break;
                        }
                        else if (animalOption == '3')  // goat
                        {
                            if (manageOption == '1')
                            {
                                goatList.addNewGoat();
                                goatList.saveToFile(goatListName);
                            }
                            else if (manageOption == '2')
                            {
                                int goatsID;
                                goatList.getInfo();
                                cout << "Enter ID to move to sold: ";
                                cin >> goatsID;
                                goatList.moveToSoldList(soldGoats, goatsID);

                            }
                            else if (manageOption == '3')
                            {
                                int goatsID; // Use int for ID
                                goatList.getInfo();
                                cout << "Enter ID to move to dead: ";
                                cin >> goatsID;
                                goatList.moveToDeadList(deadGoats, goatsID);
                            }
                            break;
                        }
                        else if (animalOption == '4') // horse
                        {
                            if (manageOption == '1')
                            {
                                horseList.addNewHorse();
                                horseList.saveToFile(horseListName);
                            }
                            else if (manageOption == '2')
                            {
                                int horseID;
                                horseList.getInfo();
                                cout << "Enter ID to move to sold: ";
                                cin >> horseID;
                                horseList.moveToSoldList(soldHorses, horseID);

                            }
                            else if (manageOption == '3')
                            {
                                int horseID;
                                horseList.getInfo();
                                cout << "Enter ID to move to dead: ";
                                cin >> horseID;
                                horseList.moveToDeadList(deadHorses, horseID);
                            }
                            break;
                        }
                        
                    }
                    break; // Break manage
                }
                case '2': // Sold list report
                {
                    if (animalOption == '1')
                    {
                        printer.soldChickens();
                    }
                    if (animalOption == '2')
                    {
                        printer.soldCows();
                    }
                    if (animalOption == '3')
                    {
                        printer.soldGoats();
                    }
                    if (animalOption == '4')
                    {
                        printer.soldHorses();
                    }
                    break;
                }
               
                case '3': // dead report
                {
                    if (animalOption == '1')
                    {
                        printer.deadChickens();
                    }
                    if (animalOption == '2')
                    {
                        printer.deadCows();
                    }
                    if (animalOption == '3')
                    {
                        printer.deadGoats();
                    }
                    if (animalOption == '4')
                    {
                        printer.deadHorses();
                    }
                    break;
                }
                case '4': // annual report
                {
                    if (animalOption == '1')
                    {
                        printer.ChickenReport();
                    }
                    if (animalOption == '2')
                    {
                        printer.CowReport();
                    }
                    if (animalOption == '3')
                    {
                        printer.GoatReport();
                    }
                    if (animalOption == '4')
                    {
                        printer.HorseReport();
                    }
                    break;
                }
                }
            }
            break; // break from main menu
        }

        case '5': // Horse Locations Menu
        {
            printer.Location();
            pause_program();
            break;
        }

        case '6': // Full Annual Report
        {
            printer.AnnualReport();
            pause_program();
            break;
        }

        default:
        {
            cout << "Invalid option. Please try again." << endl;
            break;
        }
        }
    }

    return 0; // Program terminates cleanly here
}
