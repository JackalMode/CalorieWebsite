#ifndef CALORIETRACKER_FOODDATABASE_H
#define CALORIETRACKER_FOODDATABASE_H

#include <vector>
#include <string>
#include "Food.h"
using namespace std;

class FoodDatabase {
private:
    // Static vector to hold list of foods in file/database
    static vector<Food> foods;
    // Static method to load food data from file
    static void loadFromFile(const string& filename);
    // static method to save data to file
    static void saveToFile(const string& filename);
public:
    //Constructor
    FoodDatabase();
    // Static method to add food item to file
    static void addFood(const Food& food);
    // Static method to find food
    static const Food* findFood(const string& foodName);
    // Method to remove food item
    void removeFood(const string& foodName, bool displayMess = true);
    // Method to search for foods that match a given name or partial name
    vector<Food> searchFoodByName(const string& searchTerm);
    // Method to display foods with calories less than or greater than a given value
    void displayByCalories(double calorieUL, bool showLess);
    // Method to search for foods that match a given name and have calories less than or greater than a given value
    void searchByFoodAndCalories(const string& searchTerm, double caloriesUL, bool showLess);
};
#endif //CALORIETRACKER_FOODDATABASE_H
