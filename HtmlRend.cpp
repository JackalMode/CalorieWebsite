#include "HtmlRend.h"
#include <iostream>

using namespace std;

void HtmlRend::rendCalorieResult(const string& foodName, double weight, double totalCalories){
        cout << "<!DOCTYPE html>\n";
        cout << "<html lang='en'>\n";
        cout << "<head>\n";
        cout << "<meta charset='UTF-8'>\n";
        cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
        cout << "<title>Calorie Calculation Result</title>\n";
        cout << "<link rel='stylesheet' href='cpp.css'>\n";  // Link to your CSS file
        cout << "</head>\n";
        cout << "<body>\n";
        cout << "<div class='result-container'>\n";
        cout << "<h1>Calorie Calculation Result</h1>\n";
        cout << "<p>The amount of calories in " << weight << " grams of " << foodName << " is " << totalCalories << " calories.</p>\n";
        cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
        cout << "</div>\n";
        cout << "</body>\n";
        cout << "</html>\n";
}

void HtmlRend::rendFoodNotFound(const string& foodName){
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
        cout << "<h1>Food Not Found</h1>\n";
        cout << "<p>The food \"" << foodName << "\" was not found in the database.</p>\n";
        cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n";
        cout << "</div>\n";
        cout << "</body>\n";
        cout << "</html>\n";
}