#include "HtmlRend.h"
#include "Food.h"
#include "FoodDatabase.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Displays the result of calculating the calories for a food
void HtmlRend::rendCalorieResult(const string& foodName, double weight, double totalCalories){
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Calorie Calculation Result</title>\n";
    cout << "<link rel='stylesheet' href='cpp.css'>\n";  
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='result-container'>\n";
    cout << "<h1>Calorie Calculation Result</h1>\n";
    // Display calculated calories
    cout << "<p>The amount of calories in " << weight << " grams of " << foodName << " is " << totalCalories << " calories.</p>\n";
    cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";
}
// Displays search results for a given food name
void HtmlRend::rendSearchByName(const vector<Food>& results, const string& searchTerm){
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Calorie Calculation Result</title>\n";
    cout << "<link rel='stylesheet' href='cpp.css'>\n";  
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='result-container'>\n";
    cout << "<h1>Search Results for: \"" << searchTerm << "\"</h1>\n";

    if(results.empty()){
        cout << "<p>No foods found matching " << searchTerm << ".</p>\n" << endl;
    } else {
        cout << "<ul class='food-list'>\n";
        for (const auto& food : results){
            cout << "<li>" << food.getName() << " : " << food.getCaloriesPer100g() << " calories per 100 grams</li>\n" << endl;
        }
        cout << "</ul>\n";
    } 
    cout << "</div>\n";
    cout << "<div class='back-link-container'>\n";
    cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";
}
// Displays search results based on calories, with a filter for less/greater than a limit
void HtmlRend::rendSearchByCal(const vector<Food>& foods, double calorieUL, bool showLess){
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Calorie Calculation Result</title>\n";
    cout << "<link rel='stylesheet' href='cpp.css'>\n";  
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='result-container'>\n";
    cout << "<h1>Search Results</h1>\n";
    if(foods.empty()){
        cout << "<p>No food in the database!</p>\n" << endl;
        return;
    }
    // Iterate through the foods vector and display the foods that match the criteria
    cout << "<ul>\n";
    cout << "<ul class='calorie-list'>\n";
    for(const auto& food : foods){
        double foodCalories = food.getCaloriesPer100g();
        if((showLess && foodCalories < calorieUL) || (!showLess && foodCalories > calorieUL)){
            cout << "<li>" << food.getName() << " : " << foodCalories << " calories per 100 grams</li>\n" << endl;
        }
    }
    cout << "</ul>\n";
    cout << "</div>\n";
    cout << "</div>\n";
    cout << "<div class='back-link-container'>\n";
    cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
    cout << "</body>\n";
    cout << "</html>\n";
}
// Displays search results by both name and calorie limit
void HtmlRend::rendSearchByCalName(const vector<Food>& results, const string& searchTerm, double calorieUL, bool showLess){
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Calorie Calculation Result</title>\n";
    cout << "<link rel='stylesheet' href='cpp.css'>\n";  
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='result-container'>\n";
    cout << "<h1>Search Results</h1>\n";
    // Display the search results
    if(results.empty()){
        cout << "<p>No foods found that match the search criteria.</p>\n" << endl;
    } else {
        cout << "<ul class='name-calorie-list'>\n";
        for(const auto& food : results){
            cout << "<li>" << food.getName() << " : " << food.getCaloriesPer100g() << " calories per 100 grams</li>\n" << endl;
        }
        cout << "</ul>\n";
    }
    cout << "</div>\n";
    cout << "<div class='back-link-container'>\n";
    cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";
}
// Displays the display of journal entries
void HtmlRend::rendDisplayEntries(const vector<JournalEntry>& entries){
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Calorie Calculation Result</title>\n";
    cout << "<link rel='stylesheet' href='cpp.css'>\n";  
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='result-container'>\n";
    cout << "<h1>Journal Entries</h1>\n";
    cout << "<ul class='Entries-list'>\n";
    for(const auto& entry : entries){
        if(entry.foodName.empty()){
            cout << "<p>No Entries Found</p>\n" << endl;
            return;
        }
        cout << "<li>" << entry.date << ": " << entry.foodName << " - " << entry.calories << " calories. Notes: " << entry.note << "</li>\n" << endl;
    }
    cout << "</ul>\n";
    cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";
}
// Displays the result of adding an entry to the journal
void HtmlRend::rendAddToJournal(const string& foodName, double weight, double totalCalories, const string& note) {
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Journal Entry Saved</title>\n";
    cout << "<link rel='stylesheet' href='cpp.css'>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='result-container'>\n";
    cout << "<h1>Journal Entry Saved Successfully</h1>\n";
    cout << "<p>Food: " << foodName << "</p>\n";
    cout << "<p>Weight: " << weight << " grams</p>\n";
    cout << "<p>Total Calories: " << totalCalories << " calories</p>\n";
    if (!note.empty()) {
        cout << "<p>Note: " << note << "</p>\n";
    }
    cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";
}
// Displays the result of adding a food to the database
void HtmlRend::rendAddFood(const string& foodName, bool add){
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Add Food Result</title>\n";
    cout << "<link rel='stylesheet' href='cpp.css'>\n";  
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='result-container'>\n";
    cout << "<h1>Add Food Result</h1>\n";
    if (add) {
        cout << "<p>The food \"" << foodName << "\" has been added successfully to the database.</p>\n";
    } else {
        cout << "<p>The food \"" << foodName << "\" is already in the database.</p>\n";
    }
    cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";
}
// Displays the result of removing a food from the database
void HtmlRend::rendRemoveFood(const string& foodName, bool remove){
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Add Food Result</title>\n";
    cout << "<link rel='stylesheet' href='cpp.css'>\n";  // Link to your CSS file
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='result-container'>\n";
    cout << "<h1>Add Food Result</h1>\n";
    if (remove) {
        cout << "<p>The food \"" << foodName << "\" has been removed successfully from the database.</p>\n";
    } else {
        cout << "<p>The food \"" << foodName << "\" was not found in the database.</p>\n";
    }
    cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";
}