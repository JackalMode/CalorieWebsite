#ifndef HTML_REND_H
#define HTML_REND_H
#include "Food.h"
#include "Journal.h"
#include <string>
#include <vector>
using namespace std;

class HtmlRend {
public:
    // Displays the result of calculating the calories for a food
    static void rendCalorieResult(const string& foodName, double weight, double totalCalories);
    // Displays the display of journal entries
    static void rendDisplayEntries(const vector<JournalEntry>& entries);
    // Displays search results for a given food name
    static void rendSearchByName(const vector<Food>& results, const string& searchTerm);
    // Displays search results based on calories, with a filter for less/greater than a limit
    static void rendSearchByCal(const vector<Food>& foods, double calorieUL, bool showLess);
    // Displays search results by both name and calorie limit
    static void rendSearchByCalName(const vector<Food>& foods, const string& searchTerm, double calorieUL, bool showLess);
    // Displays the result of adding an entry to the journal
    static void rendAddToJournal(const string& foodName, double weight, double totalCalories, const string& note);
    // Displays the result of adding a food to the database
    static void rendAddFood(const string& foodName, bool add);
    // Displays the result of removing a food from the database
    static void rendRemoveFood(const string& foodName, bool remove);
};

#endif