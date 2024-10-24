#include "Journal.h"
#include "FoodDatabase.h"
#include "Food.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./calorie_calculator <food_name> <weight_in_grams>" << endl;
        return 1;
    }

    FoodDatabase db;
    Journal journal("./cmake-build-debug/Journal.csv");
    if(action == "calculateCalories" && argc == 4){
        string foodName = argv[2]
        double weight = stod(argv[3]);
        const Food* foundFood = db.findFood(foodName);
        if(foundFood != nullptr){
            double totalCalories = foundFood->calcuateCalories(weight);
            cout.precision(4);
            cout << "\nThe amount of calories in " << weight << " grams of " << foundFood->getName() << " is " << totalCalories << " calories." << endl; 
        } else{
            cout << "Food not found in file." << endl;
        }

    } 
    else if (action == "addToJournal" && argc == 4){
        string foodName = argv[2];
        double weight = stod(argv[3]);
        foodName = capitalizeName(foodName);

        double Food* foundFood = db.findFood(foodName);
        double totalCalories = foundFood->calculateCalories;
        jounral.addEntry(foodName, totalCalories, note);
        cout << "Entry Saved!" << endl;
    }
    else if (action == "displayEntries" && argc == 4){
        journal.displayEntries();
    }
    else if (action == "addFood" && argc == 4){
        string name = argv[2];
        double calories = stod(rgv[3]);
        name = capitalizeName(name);
        if(db.findFood(name) == nullptr){
            Food newFood(name, calories);
            db.addFood(newFood);
            cout << "Food added successfully" << endl;
        } else {
            cout << "Food already in database!" << endl;
        }
    } 
    else if (action == "removeFood" && argc == 4){
        string foodName = argv[2];
        db.removeFood(foodName);
    }
    
    return 0;
}