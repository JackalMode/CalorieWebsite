#include <sstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "Menu.h"
#include "Food.h"
#include "Journal.h"

using namespace std;

// constructor
Menu::Menu(FoodDatabase& db) : db(db) {}

int Menu::getChoice(istream &ins) {
    string input;
    int num;
    int firstO = 0, lastO = 6;

    // Menu options for user
    cout << "Calorie Tracker Menu\n";
    cout << "1. Calculate Calories\n";
    cout << "2. Add Food\n";
    cout << "3. Remove Food\n";
    cout << "4. Display Journal Entries\n";
    cout << "5. Search Foods by Name, Calories, or Both\n";
    cout << "6. Generate Calories Graph\n";
    cout << "0. Save and Exit\n";

    // Loop to validate user input
    while (true) {
        cout << "Enter a choice:";
        getline(ins, input);


        // Handle empty input
        if (input.empty()) {
            cout << "No Input! Please enter a number between " << firstO << " and " << lastO << "." << endl;
            continue;
        }

        stringstream ss(input);

        // Check if input is a valid integer
        if (ss >> num && ss.eof()) {
            // Validate choice is within the acceptable range
            if (num >= firstO && num <= lastO) {
                return num;
            } else {
                cout << "Out of Range! Enter a number between " << firstO << " and " << lastO << "." << endl;
            }
        } else {
            cout << "Invalid Input! Please enter a valid number between " << firstO << " and " << lastO << "." << endl;
        }
    }
}

/**
 * Prompts the user to enter a weight and a unit (grams, ounces, or pounds)
 * Converts the weight to grams if necessary
 * @param in
 * @param outs
 * @return The weight of the food in grams
 */
double Menu::foodWeight(std::istream &in, std::ostream &outs) {
    double weight;
    string stringWeight, unit;
    bool valid = false;
    bool menu = false;
    // Loop until valid unit
    while(!menu){
        cout << "Enter the unit of weight:\n";
        cout << "Grams (g)\n";
        cout << "Ounces (oz)\n";
        cout << "Pounds (lbs)\n";
        cout << "Choice: ";
        getline(in, unit);
        if(unit.empty()){
            cout << "No Input!\n";
            continue;
        }
        // Convert input to lowercase
        for(char &c : unit){
            c = tolower(c);
        }

        // Validate input
        if(unit != "g" && unit != "oz" && unit != "lbs"){
            cout << "Invalid Unit! Please enter 'g' for grams, 'oz' for ounces, or 'lbs' for pounds.\n";
            continue;
        }
        menu = true;
    }

    // Loop until a valid weight
    while(!valid){
        cout << "Please enter the weight of the food:";
        getline(in, stringWeight);
        // Handle empty input
        if(stringWeight.empty()){
            cout << "No Input!\n";
            continue;
        }
        // Check if input is a valid numeric weight
        stringstream ss(stringWeight);
        if (ss >> weight && weight >= 0 && ss.eof()){
            // Convert weight to grams if necessary
            if(unit == "oz"){
                weight *= 28.3495;
            } else if (unit == "lbs"){
                weight *= 453.592;
            }
            valid = true;
        } else {
            cout << "Invalid Input! Enter a positive integer for weight in " << unit << ".\n";
        }
    }
    return weight;
}
/**
 * Prompts user to enter a food name until a valid name is entered
 * Checks if the food exists in the database
 * @return foodName
 */
string Menu::foodName() {
    string foodName;
    bool yes = false;

    // Loop until valid food name
    while(!yes) {
        cout << "\nPlease enter a food name:";
        getline(cin, foodName);
        // Handle empty input
        if(foodName.empty()){
            cout << "No Input!\n";
            continue;
        }
        foodName = Menu::capitalizeName(foodName);
        // Checks if food name is in database
        const Food *foundFood = db.findFood(foodName);
        if (foundFood == nullptr) {
            cout << "Food not found in file." << endl;
        } else {
            yes = true;
        }
    }
    return foodName;
}

/**
 * Adds a new food item to the database
 * prompts user for food name, ensures it is not already in the database
 * gets weight of the food
 */
void Menu::addFood(){
    string name;
    double calories = 0;
    string sCalories;
    // Get and validate food name
    while(true){
        cout << "Enter food name:";
        getline(cin, name);
        if(name.empty()){
            cout << "Food name cannot be empty!" << endl;
            continue;
        }
        name = capitalizeName(name);
        // Checks if food is already in file
        if(FoodDatabase::findFood(name) != nullptr){
            cout << "Food already exists in file!" << endl;
            continue;
        }
        break;
    }
    // Get and validate weight. More like make sure it's an integer
    Food food(name, calories);

    // Now call newWeight to get the weight input
    food.newWeight(cin, cout);

    // Add new food to the file.
    FoodDatabase::addFood(food);
    cout << endl;
    cout << "Food added successfully!" << endl;
}

/**
 * Calculates and displays the calories for a specific food
 * Allows user to optionally save the entry in a journal
 *
 * @param in
 * @param outs
 */
void Menu::calDisCal(std::istream &in, std::ostream &outs) {
    bool choice = false;
    // Get food name from user
    string foodName = Menu::foodName();
    // Get the weight of the food
    double weight = Menu::foodWeight(cin, cout);
    // Find food & Check if food is there
    const Food* foundFood = db.findFood(foodName);
    if (foundFood != nullptr) {
        // Get total calories
        double totalCalories = foundFood->calculateCalories(weight);
        cout.precision(4);
        cout << "\nThe amount of calories in " << weight << " grams of " << foundFood->getName() << " is " << totalCalories << " calories." << endl;
    } else {
        cout << "Food not found in file." << endl;
    }

    string journalChoice, noteChoice;
    Journal journal("cmake-build-debug/Journal.csv");
    char journalLower, noteLower;
    // Loop to decide if the user wants to save the entry
    while(!choice){
        cout << "Would you like to save it in your Journal (Y/N):";
        getline(cin , journalChoice);
        if(journalChoice.empty()){
            cout << "No Input! Enter (Y/N):";
            continue;
        }

        // Convert input to lowercase
        journalLower = tolower(journalChoice[0]);
        if(journalLower == 'y'){
            cout << "Would you like to add a note? (Y/N):";
            getline(cin, noteChoice);
            noteLower = tolower(noteChoice[0]);
            string note;
            if(noteLower == 'y'){
                cout << "Enter your note:";
                getline(cin, note);
            } else if (noteLower == 'n'){
                note = "";
            }

            // Save entry to journal
            double totalCalories = foundFood->calculateCalories(weight);
            journal.addEntry(foodName, totalCalories, note);
            cout << "Entry Saved!" << endl;
            choice = true;

        } else if (journalLower == 'n'){
            choice = true;
        } else {
        cout << "Invalid Input! Enter 'Y' for yes and 'N' for no:";
        }
    }

}

/**
 * Displays all journal entries
 */
void Menu::displayEnt() {
    Journal journal("cmake-build-debug/Journal.csv");
    journal.displayEntries();
}

/**
 * Capitalizes the first letter of each word in the given food name
 * Used for consistent formatting
 *
 * @param userInputFood
 * @return userInputFood: Formatted food name
 */
string Menu::capitalizeName(string userInputFood){
    // Capitalize the first letter of each word and lowercase the rest of the letters
    for(int x = 0; x < userInputFood.length(); x++){
        if(x == 0 || userInputFood[x - 1] == ' '){
            userInputFood[x] = toupper(userInputFood[x]);
        } else {
            userInputFood[x] = tolower(userInputFood[x]);
        }
    }
    return userInputFood;
}

/**
 * Removes a food item from the database
 * @param db
 */
void Menu::removeFromData(FoodDatabase& db) {
    string foodName;
    // Prompt the user for the name of the food
    cout << "Enter the name of the food to remove: ";
    getline(cin, foodName);
    // Remove the food
    db.removeFood(foodName);
}

/**
 * Searches for foods by name in the database
 */
void Menu::searchByFoodName() {
    string searchTerm;
    bool input = false;
    // Loop until a valid search term
    while(!input){
        cout << "Enter the food name or part of the name to search:";
        getline(cin, searchTerm);
        if(searchTerm.empty()){
            cout << "No Input!\n";
            continue;
        }
        input = true;
    }

    // Search for matching foods in the database
    vector<Food> results = db.searchFoodByName(searchTerm);

    if(results.empty()){
        cout << "No foods found matching " << searchTerm << "." << endl;
    } else {
        cout << "Matching Foods:" << endl;
        cout << "---------------" << endl;
        for (const auto& food : results){
            cout << food.getName() << " : " << food.getCaloriesPer100g() << " calories per 100 grams" << endl;
        }
    }

}

/**
 * Searches for foods based on calorie content
 * @param db
 */
void Menu::searchByCalories(FoodDatabase &db) {
    double caloriesUL;
    bool validCalories = false, validChoice = false;
    char filter;
    // Loop until a valid calorie threshold
    while(!validCalories){
        string stringCaloriesUL;
        cout << "Enter the calories threshold:";
        getline(cin, stringCaloriesUL);

        if(stringCaloriesUL.empty()){
            cout << "No Input! Please enter a valid number." << endl;
            continue;
        }
        stringstream ss(stringCaloriesUL);
        // Validate that the input is a positive number
        if(ss >> caloriesUL && caloriesUL >= 0 && ss.eof()){
            validCalories = true;
        } else {
            cout << "Invalid Input! Enter a positive number." << endl;
        }
    }
    // Loop until user gives valid input on whether they want to show foods less than or great than
    while(!validChoice){
        string stringShowLess;
        cout << endl;
        cout << "Show foods with calories less than (L) or greater than (G) " << caloriesUL << "?:";
        getline(cin, stringShowLess);
        cout << endl;

        if(stringShowLess.empty()){
            cout << "No Input! Please enter 'L' or 'G'." << endl;
            continue;
        }
        filter = tolower(stringShowLess[0]);
        if(filter == 'l' || filter == 'g'){
            break;
        } else {
            cout << "Invalid Choice! Enter 'L' for less than or 'G' for greater than." << endl;
        }

    }
    // Display filtered results
    db.displayByCalories(caloriesUL, filter == 'l');

}

/**
 * searches for foods based on the user's choice of filtering by name, calories, or both
 * @param db
 */
void Menu::searchByChoice(FoodDatabase& db) {
    string choice;
    bool valid = false;
    char filter;

    // Loop until user chooses a valid filter option
    while(!valid){
        cout << "How would you like to filter the foods?\n";
        cout << "1. By Name\n";
        cout << "2. By Calories\n";
        cout << "3. By Both Name and Calories\n";
        cout << "Please enter your choice (1/2/3): ";
        getline(cin, choice);
        if(choice.empty()){
            cout << "No Input! Enter a valid choice." << endl;
            continue;
        }
        // Handle choice by name
        if (choice == "1") {
            Menu::searchByFoodName();
            valid = true;
        }
        // Handle choice by calories
        else if (choice == "2") {
            Menu::searchByCalories(db);
            valid = true;
        }
        // Handle choice by both
        else if (choice == "3") {
            string searchTerm;
            double calorieUL;
            string filterChoice;
            bool input = false, validChoice = false, validCalories = false;

            // Get the food name/part name to search
            while(!input){
                cout << "Enter the food name or part of the name to search:";
                getline(cin, searchTerm);
                if(searchTerm.empty()){
                    cout << "No Input!\n";
                    continue;
                }
                input = true;
            }
            // Get calorie threshold
            while(!validCalories){
                string stringCaloriesUL;
                cout << "Enter the calories threshold:";
                getline(cin, stringCaloriesUL);

                if(stringCaloriesUL.empty()){
                    cout << "No Input! Please enter a valid number." << endl;
                    continue;
                }
                stringstream ss(stringCaloriesUL);
                if(ss >> calorieUL && calorieUL >= 0 && ss.eof()){
                    validCalories = true;
                } else {
                    cout << "Invalid Input! Enter a positive number." << endl;
                }
            }

            // Loop until user gives valid input on whether they want to show foods less than or great than
            while(!validChoice){
                string stringShowLess;
                cout << endl;
                cout << "Show foods with calories less than (L) or greater than (G) " << calorieUL << "?:";
                getline(cin, stringShowLess);
                cout << endl;

                if(stringShowLess.empty()){
                    cout << "No Input! Please enter 'L' or 'G'." << endl;
                    continue;
                }
                filter = tolower(stringShowLess[0]);
                if(filter == 'l' || filter == 'g'){
                    break;
                } else {
                    cout << "Invalid Choice! Enter 'L' for less than or 'G' for greater than." << endl;
                }
            }
            db.searchByFoodAndCalories(searchTerm, calorieUL, filter == 'l');
            valid = true;
        }
        else {
            cout << "Invalid choice! Please enter 1, 2, or 3.\n";
        }
    }
}

void Menu::generateGraph(){
    string command = "py JournalGraph.py";
    int retCode = system(command.c_str());

    if(retCode != 0){
        cout << "Failed to generate graph!" << endl;
    }   
}
