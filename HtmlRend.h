#ifndef HTML_REND_H
#define HTML_REND_H
#include "Food.h"
#include "Journal.h"
#include <string>
#include <vector>
using namespace std;

class HtmlRend {
public:
    static void rendCalorieResult(const string& foodName, double weight, double totalCalories);
    static void rendFoodNotFound(const string& foodName);
    static void rendDisplayEntries(const vector<JournalEntry>& entries);
    static void rendSearchByName(const vector<Food>& results, const string& searchTerm);
    static void rendSearchByCal(const vector<Food>& foods, double calorieUL, bool showLess);
    static void rendSearchByCalName(const vector<Food>& foods, const string& searchTerm, double calorieUL, bool showLess);
    static void rendAddToJournal(const string& foodName, double weight, double totalCalories, const string& note);
    static void rendAddFood(const string& foodName, bool add);
    static void rendRemoveFood(const string& foodName, bool remove);
};

#endif