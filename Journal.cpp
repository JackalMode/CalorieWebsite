#include "Journal.h"
#include "HtmlRend.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include "Food.h"

using namespace  std;

/**
 * Constructor that initializes the Journal by loading entries from a provided file
 * @param fileName
 */
Journal::Journal(const string &fileName) : fileName(fileName) {
    loadFromFile(fileName);
}

/**
 * Gets the current date in the format "YYYY-MM-DD"
 * @return Current date as a string
 */
string Journal::getCurrentDate() {
    const std::chrono::time_point now{std::chrono::system_clock::now()};
    const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
    stringstream ss;
    ss << int(ymd.year()) << "-" << unsigned(ymd.month()) << "-" << unsigned(ymd.day());
    return ss.str();

}

/**
 * Adds a new entry to the jounral, including food name, calories, and an optional note
 * @param foodName
 * @param calories
 * @param note
 */
void Journal::addEntry(const std::string &foodName, double calories, const std::string &note) {
    // Check if the food name is empty or calories are negative
    if (foodName.empty() || calories < 0) {
        cout << "Invalid entry: foodName cannot be empty and calories must be greater than or equal to zero." << endl;
        return;
    }
    // Add the new entry to the journal
    entries.emplace_back(getCurrentDate(), foodName, calories, note);
    saveToFile(fileName);
}

/**
 * Displays all the entries in the journal
 */
void Journal::displayEntries() {
   HtmlRend::rendDisplayEntries(entries);
}

/**
 * Saves all the current entries to a file
 * @param fileName
 */
void Journal::saveToFile(const std::string &fileName) const {
    ofstream outFile(fileName);
    if(!outFile.is_open()){
        cout << "Error opening file " << fileName << endl;
        return;
    }
    // Write each entry to the file
    for(const auto& entry : entries){
        outFile << entry.date << "," << entry.foodName << "," << entry.calories << "," << entry.note << "\n";
    }
    outFile.close();

}

/**
 * Loads all journal entries from a specified file
 * @param fileName
 */
void Journal::loadFromFile(const std::string &fileName) {
    ifstream inFile(fileName);
    if(!inFile.is_open()){
        cout << "Error opening file " << fileName << endl;
        return;
    }
    string line;
    // Read each line from the file
    while(getline(inFile, line)){
        string date, foodName, note;
        double calories;
        stringstream ss(line);
        getline(ss, date, ',');
        getline(ss, foodName, ',');
        ss >> calories;
        ss.ignore();
        getline(ss, note);

        // Add entry to journal if valid
        if(!foodName.empty() && calories >= 0){
            entries.emplace_back(date, foodName, calories, note);
        }
    }
    inFile.close();
}

/**
 * Returns the number of entries currently in the journal
 * @return number of journal entries
 */
int Journal::getEntryCount() const {
    return entries.size();
}