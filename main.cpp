#include "Journal.h"
#include "FoodDatabase.h"
#include "Food.h"
#include "Menu.h"
#include "HtmlRend.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: No action specified." << endl;
        return 1;
    }

    
    FoodDatabase db;
    Journal journal("./cmake-build-debug/Journal.csv");
    string action = argv[1];
    if (action == "calcCalories" && argc == 4) {
        string foodName = argv[2];
        double weight = stod(argv[3]);
        foodName = Menu::capitalizeName(foodName);
        const Food* foundFood = db.findFood(foodName);
        if (foundFood) {
            double totalCalories = foundFood->calculateCalories(weight);
            HtmlRend::rendCalorieResult(foodName, weight, totalCalories);
        } else {
            HtmlRend::rendFoodNotFound(foodName);
        }
    }
    else if (action == "addToJournal" && argc == 5){
        string foodName = argv[2];
        double weight = stod(argv[3]);
        string note = argv[4];
        foodName = Menu::capitalizeName(foodName);
        const Food* foundFood = db.findFood(foodName);
        double totalCalories = foundFood->calculateCalories(weight);
        journal.addEntry(foodName, totalCalories, note);
        cout << "Entry Saved!" << endl;
    }
    else if (action == "displayEntries"){
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
    else if (action == "removeFood" && argc == 3){
        string foodName = argv[2];
        foodName = Menu::capitalizeName(foodName);
        db.removeFood(foodName);
    }
    else if (action == "searchFoodByName" && argc == 3){
        string searchTerm =argv[2];
        searchTerm = Menu::capitalizeName(searchTerm);
        vector<Food> results = db.searchFoodByName(searchTerm);
        if(results.empty()){
            cout << "No foods found matching " << searchTerm << "." << endl;
        } else {
            for (const auto& food : results){
                cout << food.getName() << " : " << food.getCaloriesPer100g() << " calories per 100 grams" << endl;
            }
        } 
    }
    else if (action == "displayByCalories" && argc == 4) {
        double calorieLimit = stod(argv[2]);
        char filter = argv[3][0];
        db.displayByCalories(calorieLimit, filter == 'l');
    }
    else if (action == "searchByBoth" && argc == 5) {
        string searchTerm = argv[2];
        searchTerm = Menu::capitalizeName(searchTerm);
        double calorieLimit = stod(argv[3]);
        char filter = argv[4][0];
        db.searchByFoodAndCalories(searchTerm, calorieLimit, filter == 'l');
    }
    else if (action == "generateGraph"){
        system("py JournalGraph.py");
    } else {
        cout << "Error generating Graph!" << endl;
    }
    
    return 0;
}