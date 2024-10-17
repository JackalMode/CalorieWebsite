#ifndef CALORIETRACKER_FOOD_H
#define CALORIETRACKER_FOOD_H
#include <string>
using namespace std;

class Food{
private:
    string name;
    double caloriesPer100g{};

public:
    // Constructor to initialize a food object
    Food(const string& foodName, double calPer100g);
    // Calculates the weight of new food
    double newWeight(istream &in, ostream &outs);
    // Calculates the calories for a given weight of food
    [[nodiscard]] double calculateCalories(double weight) const;
    // Returns the name of the food
    [[nodiscard]] string getName() const;
    // Returns the number of calories per 100 grams
    [[nodiscard]] double getCaloriesPer100g() const;
    // overloaded equality operator
    bool operator==(const Food& other) const;
};
#endif //CALORIETRACKER_FOOD_H
