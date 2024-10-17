#include "Journal.h"
#include "FoodDatabase.h"
#include "Food.h"
#include <iostream>
#include <ctime>

using namespace std;

bool testJournal();
bool testFoodDatabase();
bool testFood();

int main() {
    srand(time(NULL));
    if(testJournal()){
        cout << "Passed all Journal test cases" << endl;
    }
    if(testFood()){
        cout << "Passes all Food test cases" << endl;
    }
    if(testFoodDatabase()){
        cout << "Passed all FoodDatabase test cases" << endl;
    }
    return 0;
}

bool testFood(){
    bool passed = true;
    // Test Food constructor and getters
    Food apple("Apple", 52.0);
    if(apple.getName() != "Apple" || apple.getCaloriesPer100g() != 52.0){
        passed = false;
        cout << "Failed Food constructor or getters test" << endl;
    }
    // Test overloaded equality operator
    Food anotherApple("Apple", 55.0);
    if(!(apple == anotherApple)){
        passed = false;
        cout << "Failed Food operator== test case" << endl;
    }
    // Test calculateCalories method
    double calculatedCalories = apple.calculateCalories(200.0);
    if (calculatedCalories != 104.0) {
        passed = false;
        cout << "Failed Food calculateCalories test case" << endl;
    }
    // Test newWeight method with oz
    stringstream inputOz("oz\n10\n150\n");
    stringstream outputOz;
    Food testFoodOz("TestFoodOz", 0.0);
    double updatedCaloriesOz = testFoodOz.newWeight(inputOz, outputOz);

    double expectedCaloriesOz = (150.0 / (10 * 28.3495)) * 100.0;
    if (updatedCaloriesOz != expectedCaloriesOz) {
        passed = false;
        cout << "Failed Food newWeight test case for ounces" << endl;
    }
    // Test newWeight method with lbs
    stringstream inputLbs("lbs\n1\n150\n");
    stringstream outputLbs;
    Food testFoodLbs("TestFoodLbs", 0.0);
    double updatedCaloriesLbs = testFoodOz.newWeight(inputLbs, outputLbs);

    double expectedCaloriesLbs = (150.0 / (1 * 453.592)) * 100.0;
    if (updatedCaloriesLbs != expectedCaloriesLbs) {
        passed = false;
        cout << "Failed Food newWeight test case for pounds" << endl;
    }
    
    return passed;
}

bool testFoodDatabase(){
    bool passed = true;
    FoodDatabase foodDb;
    // Test adding a food item
    Food testTest("testTest" , 89.0);
    FoodDatabase::addFood(testTest);
    // Test finding a food item
    const Food* foundFood = FoodDatabase::findFood("testTest");
    if(foundFood == nullptr || foundFood->getName() != "testTest"){
        passed = false;
        cout << "Failed foodDatabase findFood test case" << endl;
    }
    // Test removing a food item
    foodDb.removeFood("testTest", false);
    foundFood = FoodDatabase::findFood("testTest");
    if (foundFood != nullptr){
        passed = false;
        cout << "Failed foodDatabase removeFood test case" << endl;
    }
    // Test searching by name
    Food capt("Captainss", 2000.0);
    FoodDatabase::addFood(capt);
    Food pain("Painss", 2000.0);
    FoodDatabase::addFood(pain);
    vector<Food> searchResults = foodDb.searchFoodByName("ainss");
    if(searchResults.size() != 3){
        passed = false;
        cout << "Failed foodDatabase searchFoodByName test case" << endl;
    }
    // Test searching by calories greater than
    vector<Food> allFoods = foodDb.searchFoodByName("");
    int calorieCount = 0;
    for (const auto& food : allFoods) {
        if (food.getCaloriesPer100g() > 1500.0) {
            calorieCount++;
        }
    }
    if (calorieCount != 2) {
        passed = false;
        cout << "Failed foodDatabase displayByCalories test case." << endl;
    }

    // Testing searching food by name and calories less than
    Food ain("Tainsss", 0);
    FoodDatabase::addFood(ain);
    vector<Food> filteredResults = foodDb.searchFoodByName("ainsss");
    int count = 0;
    for (const auto& food : filteredResults) {
        if (food.getCaloriesPer100g() < 1) {
            count++;
        }
    }
    if (count != 1) {
        passed = false;
        cout << "Failed foodDatabase searchByFoodAndCalories test case." << endl;
    }
    return passed;

}

bool testJournal() {
    bool passed = true;
    // Create a test journal file to avoid modifying the original one
    ofstream ofs("TestJournal.csv", ofstream::out | ofstream::trunc);
    ofs.close();

    Journal journal("TestJournal.csv");
    // Test adding entries to the journal
    journal.addEntry("Orange", 62.0, "Morning snack");
    journal.addEntry("Cereal", 150.0, "Breakfast");

    if(journal.getEntryCount() != 2){
        passed = false;
        cout << "Failed Journal addEntry test case" << endl;
    }
    // Test to validate the getCurrentDate method
    string currentDate = Journal::getCurrentDate();
    if (currentDate.empty() || currentDate.length() < 8 || currentDate.length() > 10) {  // Basic validation of format length
        passed = false;
        cout << "Failed Journal getCurrentDate test case" << endl;
    }
    // Test saving and loading journal entries
    journal.saveToFile("test_journal.csv");
    Journal loadedJournal("test_journal.csv");
    if (loadedJournal.getEntryCount() != journal.getEntryCount()) {
        passed = false;
        cout << "Failed Journal loadFromFile test case" << endl;
    }

    return passed;
}


