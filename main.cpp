#include "FoodDatabase.h"
#include "Menu.h"
#include "Journal.h"
#include <iostream>
#include <chrono>


using namespace std;

int main() {
    cout << "Welcome to Calorie Tracker!" << endl;
    cout << "---------------------------" << endl;
    // Create instances of FoodDatabase, Menu, and Journal classes
    FoodDatabase db;
    Menu menu(db);
    Journal journal("Journal.csv");
    int choice = 1000000;
    // Loop until user choose to exit
    while (choice != 0){
        // Get users menu choice
        choice = Menu::getChoice(cin);
        switch(choice)
        {
            // Calculate Calories
            case 1: {
                menu.calDisCal(cin, cout);
                break;
            }
            // Add Food
            case 2: {
                menu.addFood();
                break;
            }
            // Remove Food
            case 3: {
                menu.removeFromData(db);
                break;
            }
            // Display Journal Entries
            case 4: {
                menu.displayEnt();
                break;
            }
            // Search Food by Name, Calories or Both
            case 5: {
                menu.searchByChoice(db);
                break;
            }
            // Generate Graph
            case 6: {
                menu.generateGraph();
                break;
            }
            case 0: {
                cout << "Exiting the program." << endl;
                break;
            }
        }
    }

  return 0;
}
