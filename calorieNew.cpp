#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./calorie_calculator <food_name> <weight_in_grams>" << endl;
        return 1;
    }

    string foodName = argv[1];
    double weight;
    stringstream(argv[2]) >> weight;

    // For simplicity, we'll use hardcoded calorie values (e.g., 52 calories per 100 grams for Apple)
    double caloriesPer100g = 52.0;  // Replace with actual logic if needed
    double totalCalories = (caloriesPer100g / 100) * weight;

    cout << "Calories in " << weight << " grams of " << foodName << ": " << totalCalories << " calories" << endl;

    return 0;
}