#include "Food.h"
#include <sstream>
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>
using namespace std;
/**
 * Constructor
 * Initializes a food obeject
 * @param foodName
 * @param calPer100g
 */
Food::Food(const string& foodName, double calPer100g) {
    name = foodName;
    caloriesPer100g = calPer100g;
}

/**
 * Calculates the calories for a given weight of food
 * @param weight
 * @return
 */
double Food::calculateCalories(double weight) const {
    return (caloriesPer100g / 100) * weight;
}

/**
 * Returns the name of the food
 * @return
 */
string Food::getName() const {
    return name;
}

/**
 * Returns the number of calories per 100 grams
 * @return
 */
double Food::getCaloriesPer100g() const {
    return caloriesPer100g;
}

/**
 * Overloaded equally operator to compare two food objects
 * @param other
 * @return
 */
bool Food::operator==(const Food &other) const {
    return this->name == other.name;
}

double Food::newWeight(istream &in, ostream &outs) {
    double weight = 0, weightInGrams = 0, caloriesInWeight = 0;
    string stringWeight, unit, stringCalories;
    bool validCal = false, menu = false, valid = false;
    while(!menu){
        outs << "Enter the unit of weight:\n";
        outs << "Grams (g)\n";
        outs << "Ounces (oz)\n";
        outs << "Pounds (lbs)\n";
        outs << "Choice: ";
        getline(in, unit);
        if (unit.empty()) {
            outs << "No Input!\n";
            continue;
        }
        for (char &c: unit) {
            c = tolower(c);
        }
        if (unit != "g" && unit != "oz" && unit != "lbs") {
            outs << "Invalid Unit! Please enter 'g' for grams, 'oz' for ounces, or 'lbs' for pounds.\n";
            continue;
        }
        menu = true;
    }
    // Loop until valid weight
    while (!valid) {
        outs << "Please enter the weight of the food:";
        getline(in, stringWeight);
        // Handle empty input
        if (stringWeight.empty()) {
            outs << "No Input!\n";
            continue;
        }
        // Check if input is a valid numeric weight
        stringstream ss(stringWeight);
        if (ss >> weight && weight >= 0 && ss.eof()) {
            if (unit == "g") {
                weightInGrams = weight;
            } else if (unit == "oz") {
                weightInGrams = weight *= 28.3495;
            } else if (unit == "lbs") {
                weightInGrams = weight *= 453.592;
            }
            valid = true;
        } else {
            outs << "Invalid Input! Enter a positive integer for weight in grams.\n";
        }
    }
    while(!validCal){
        outs << "Please enter the number of calories in " << stringWeight << " " << unit << ": ";
        getline(in, stringCalories);

        stringstream  ssCalories(stringCalories);
        if (ssCalories >> caloriesInWeight && caloriesInWeight >= 0 && ssCalories.eof()) {
            validCal = true;
        } else {
            outs << "Invalid input! Enter a positive number for calories.\n";
        }
    }
    caloriesPer100g = (caloriesInWeight / weightInGrams) * 100.0;
    return caloriesPer100g;
}

