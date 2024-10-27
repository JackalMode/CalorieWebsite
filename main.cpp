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
    // Ensure that the program has been called with an action agrument
    if (argc < 2) {
        cout << "Error: No action specified." << endl;
        return 1;
    }


    FoodDatabase db;
    Journal journal("./cmake-build-debug/Journal.csv");
    // Get the action passed from the command line
    string action = argv[1];
    // Action to calc calories
    if (action == "calcCalories" && argc == 4) {
        string foodName = argv[2];
        double weight = stod(argv[3]);
        foodName = Menu::capitalizeName(foodName);
        const Food* foundFood = db.findFood(foodName);
        if (foundFood) {
            // Calculate the total calories and 'render' (display in html code) the result
            double totalCalories = foundFood->calculateCalories(weight);
            HtmlRend::rendCalorieResult(foodName, weight, totalCalories);
        } else {
            HtmlRend::rendFoodNotFound(foodName);
        }
    }
    // Action to add a food entry to Journal
    else if (action == "addToJournal" && argc == 5){
        string foodName = argv[2];
        double weight = stod(argv[3]);\
        string note = argv[4];
        foodName = Menu::capitalizeName(foodName);
        const Food* foundFood = db.findFood(foodName);
        if(foundFood){
            // Calculate calories and add entry to the journal
            double totalCalories = foundFood->calculateCalories(weight);
            journal.addEntry(foodName, totalCalories, note);
            HtmlRend::rendAddToJournal(foodName, weight, totalCalories, note);
        } else {
            HtmlRend::rendFoodNotFound(foodName);
        }
       
    }
    // Action to display all entries in the journal
    else if (action == "displayEntries"){
        journal.displayEntries();
    }
     // Action to add a new food to the food database
    else if (action == "addFood" && argc == 4){
        string name = argv[2];
        double calories = stod(argv[3]);
        name = Menu::capitalizeName(name);
         // Add new food if it does not exist
        if(db.findFood(name) == nullptr){
            Food newFood(name, calories);
            db.addFood(newFood);
            HtmlRend::rendAddFood(name, true);
        } else {
            HtmlRend::rendAddFood(name, false);
        }
    } 
    // Action to remove a food from the food database
    else if (action == "removeFood" && argc == 3){
        string foodName = argv[2];
        foodName = Menu::capitalizeName(foodName);
        // Remove the specified food from the database
        db.removeFood(foodName);
    }
    // Action to search for a food by its name
    else if (action == "searchFoodByName" && argc == 3){
        string searchTerm =argv[2];
        searchTerm = Menu::capitalizeName(searchTerm);
        // Search the food database for matching foods
        vector<Food> results = db.searchFoodByName(searchTerm);
        HtmlRend::rendSearchByName(results, searchTerm);
    }
    // Action to display foods by calorie limit with a filter (less or greater)
    else if (action == "displayByCalories" && argc == 4) {
        double calorieLimit = stod(argv[2]);
        char filter = argv[3][0];
        // Display foods based on the specified calorie limit and filter
        db.displayByCalories(calorieLimit, filter == 'l');
    }
    // Action to search by both food name and calorie limit
    else if (action == "searchByBoth" && argc == 5) {
        string searchTerm = argv[2];
        searchTerm = Menu::capitalizeName(searchTerm);
        double calorieLimit = stod(argv[3]);
        char filter = argv[4][0];
        // Search foods by both name and calories based on the specified filter
        db.searchByFoodAndCalories(searchTerm, calorieLimit, filter == 'l');
    }
    // Action to generate a graph of journal entries using Python
    else if (action == "generateGraph"){
        // Call the Python script to generate the  graph
        system("py JournalGraph.py");
    } else {
        cout << "Error generating Graph!" << endl;
    }
    
    return 0;
}