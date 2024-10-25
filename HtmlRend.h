#ifndef HTML_REND_H
#define HTML_REND_H
#include <string>
using namespace std;

class HtmlRend {
public:
    static void rendCalorieResult(const string& foodName, double weight, double totalCalories);
    static void rendFoodNotFound(const string& foodName);
};

#endif