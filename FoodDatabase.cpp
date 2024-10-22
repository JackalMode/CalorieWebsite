#include "FoodDatabase.h"
#include "Food.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
// Initialize the static vector of food objects
vector<Food> FoodDatabase::foods;
// Constructor
FoodDatabase::FoodDatabase(){
    // Loads food data from a file
    loadFromFile("cmake-build-debug/Foods.csv");
}

/**
 * Adds food item to the database if not already there
 * saves the updated list to the file
 * @param food
 */
void FoodDatabase::addFood(const Food &food) {
    if(findFood(food.getName()) == nullptr){
        foods.push_back(food);
    }
    saveToFile("cmake-build-debug/Foods.csv");
}
/**
 * Finds food item by name returns pointer or nullptr if not there
 * @param foodName
 * @return
 */
const Food *FoodDatabase::findFood(const string &foodName) {
    for(const auto& food : foods){
        if(food.getName() == foodName){
            return &food;
        }
    }
    return nullptr;
}

/**
 * Loads food data from a file into the database
 * @param filename
 */
void FoodDatabase::loadFromFile(const std::string &filename) {
    ifstream inputFile(filename);
    if(!inputFile.is_open()){
        cout << "Error opening file " << filename << endl;
        return;
    }
    string line;
    //getline(inputFile, line);
    while(getline(inputFile, line)){
        string fName, category, per100;
        double calories;
        stringstream  ss(line);
        //getline(ss, category, ',');
        getline(ss, fName, ',');
        //getline(ss, per100, ',');
        ss >> calories;

        if(!fName.empty() && calories >= 0){
            foods.emplace_back(Food(fName, calories));
        }
    }
    inputFile.close();

}
/**
 * Saves the current list of foods to the file
 * @param filename
 */
void FoodDatabase::saveToFile(const std::string &filename) {
    ofstream outFile(filename);
    if(!outFile.is_open()){
        cout << "Error opening file " << filename << endl;
        return;
    }
    for(const auto& food : foods){
        outFile << food.getName() << "," << food.getCaloriesPer100g() << endl;
    }
    outFile.close();
}

/**
 * Removes a food item from the database
 * @param foodName
 */
void FoodDatabase::removeFood(const std::string &foodName, bool displayMessage) {
    if(foodName.empty()){
        cout << "Food Name cannot be Empty" << endl;
        return;
    }

    bool found = false;
    // Iterate through the foods vector to find the specified food
    for (size_t i = 0; i < foods.size(); i++){
        if(foods[i].getName() == foodName){
            // Remove the food from the vector
            foods.erase(foods.begin() + i);
            if(displayMessage){
                cout << foodName << " has been removed from the food database." << endl;
            }
            found = true;
            break;
        }
    }

    if(!found) {
        if(displayMessage){
            // If food is not found, print message
            cout << foodName << " not found in the food database." << endl;
        }

    }
    // Save the updated list
    saveToFile("Foods.csv");
}

/**
 * Searches the food database for foods the match the given search term
 * @param searchTerm
 * @return results
 */
vector<Food> FoodDatabase::searchFoodByName(const std::string &searchTerm) {
    vector<Food> results;
    string lowerSearchTerm = searchTerm;

    // Convert search term to lowercase for case-insensitive search
    transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);

    // Iterate through the foods vector and search for match food anmes
    for(const auto& food : foods){
        string lowerName = food.getName();
        // Convert food name to lowercase for case-insensitive comparison
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        if(lowerName.find(lowerSearchTerm) != string::npos){
            // Add matching food to the results vector
            results.push_back(food);
        }
    }
    return results;
}

/**
 * Displays all the foods in the database that have calories less than or greater than the given value
 * @param calorieUL
 * @param showLess
 */
void FoodDatabase::displayByCalories(double calorieUL, bool showLess) {
    if(foods.empty()){
        cout << "No food in the database!" << endl;
        return;
    }
    cout << endl;
    cout << "Foods with calories " << (showLess ? "less than " : "greater than ") << calorieUL << " per 100 grams:" << endl;
    cout << "----------------------------------------------------" << endl;
    // Iterate through the foods vector and display the foods that match the criteria
    for(const auto& food : foods){
        double foodCalories = food.getCaloriesPer100g();
        if((showLess && foodCalories < calorieUL) || (!showLess && foodCalories > calorieUL)){
            cout << food.getName() << " : " << foodCalories << " calories per 100 grams" << endl;
        }
    }
}

/**
 * Searches the food database for foods that match the given search term and have calories less than or greater than a given value
 * @param searchTerm
 * @param caloriesUL
 * @param showLess
 */
void FoodDatabase::searchByFoodAndCalories(const std::string &searchTerm, double caloriesUL, bool showLess) {
    vector<Food> results;
    string lowerSearch = searchTerm;
    // Convert search term to lowercase for case-insensitive search
    transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);

    // Iterate through the foods vector and search for foods that match both the name and calorie criteria
    for (const auto& food : foods){
        string lowerName = food.getName();
        // Convert food name to lowercase for case-insensitive comparison
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        double foodCalories = food.getCaloriesPer100g();
        if(lowerName.find(searchTerm) != string::npos && ((showLess && foodCalories < caloriesUL) || (!showLess && foodCalories > caloriesUL))){
            // Add matching food to the results vector
            results.push_back(food);
        }
    }
    // Display the search results
    if(results.empty()){
        cout << "No foods found that match the search criteria." << endl;
    } else {
        cout << "Matching foods with " << (showLess ? "less than " : "greater than ") << caloriesUL << " calories:" << endl;
        cout << "----------------------------------------------------" << endl;
        for(const auto& food : results){
            cout << food.getName() << " : " << food.getCaloriesPer100g() << " calories per 100 grams" << endl;
        }
    }
}