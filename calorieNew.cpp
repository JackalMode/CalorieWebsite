#include "Journal.h"
#include "FoodDatabase.h"
#include "Food.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./calorie_calculator <food_name> <weight_in_grams>" << endl;
        return 1;
    }

    FoodDatabase db;
    Journal journal("./cmake-build-debug/Journal.csv");
    string action = argv[1];
    if(action == "calculateCalories" && argc == 4){
        string foodName = argv[2];
        double weight = stod(argv[3]);
        const Food* foundFood = db.findFood(foodName);
        if(foundFood != nullptr){
            double totalCalories = foundFood->calculateCalories(weight);
            cout.precision(4);
            cout << "\nThe amount of calories in " << weight << " grams of " << foundFood->getName() << " is " << totalCalories << " calories." << endl; 
        } else{
            cout << "Food not found in file." << endl;
        }

    } 
    else if (action == "addToJournal" && argc == 4){
        string foodName = argv[2];
        double weight = stod(argv[3]);
        foodName = Menu::capitalizeName(foodName);
        const Food* foundFood = db.findFood(foodName);
        double totalCalories = foundFood->calculateCalories(weight);
        journal.addEntry(foodName, totalCalories, "");
        cout << "Entry Saved!" << endl;
    }
    else if (action == "displayEntries" && argc == 4){
        journal.displayEntries();
    }
    else if (action == "addFood" && argc == 4){
        string name = argv[2];
        double calories = stod(argv[3]);
        name = Menu::capitalizeName(name);
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
    else if (action == "searchFood" && argc == 3){
        string searchCriteria = argv[2];
        if (searchCriteria == "name" && argc == 4){
            string searchTerm = argv[3];
            vector<Food> results = db.searchFoodByName(searchTerm);
            if(results.empty()){
                cout << "No foods found matching " << searchTerm << "." << endl;
            } else {
                for (const auto& food : results){
                    cout << food.getName() << " : " << food.getCaloriesPer100g() << " calories per 100 grams" << endl;
                }
            }
        }
        else if (searchCriteria == "calories" && argc == 4) {
            double calorieLimit = stod(argv[3]);
            char filter = 'l';
            db.displayByCalories(calorieLimit, filter == 'l');
        }
        else if (searchCriteria == "both" && argc == 5){
            string foodName = argv[3];
            double calorieLimit = stod(argv[4]);
            char filter = 'l';
            db.searchByFoodAndCalories(foodName, calorieLimit, filter == 'l');
        }
    }
    else if (action == "generateGraph"){
        system("py JournalGraph.py");
    } else {
        cout << "Error generating Graph!" << endl;
    }
    
    return 0;
}