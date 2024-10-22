#ifndef CALORIETRACKER_MENU_H
#define CALORIETRACKER_MENU_H

#include <iostream>
#include <string>
#include "FoodDatabase.h"
using namespace std;

class Menu{
private:
    // Reference to a Fooddatabase object
    FoodDatabase& db;
public:
    // Constructor
    Menu(FoodDatabase& db);
    // Method to get weight of food from user input
    double foodWeight(istream &in, ostream &outs);
    // Method to get food name from user
    string foodName();
    // Static method to get user choice
    static int getChoice(istream &ins);
    // Method to add food
    void addFood();
    // Method to Calculate and Display calories
    void calDisCal(istream &in, ostream &outs);
    // Method to remove food
    void removeFromData(FoodDatabase& db);
    // Method toupper and to lower letters
    static string capitalizeName(string text);
    // Method to search food by name or part of name
    void searchByFoodName();
    // Method to search food by calories, either by less than or greater than
    void searchByCalories(FoodDatabase& db);
    // Method to search food by either name, calories, or both
    void searchByChoice(FoodDatabase& db);
    // Method to display all entries in the journal
    void displayEnt();
    // Method to display journal entries on a graph
    void generateGraph();
};

#endif //CALORIETRACKER_MENU_H
