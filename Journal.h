#ifndef CALORIETRACKER_JOURNAL_H
#define CALORIETRACKER_JOURNAL_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class JournalEntry {
public:
    string date;
    string foodName;
    double calories;
    string note;

    // Constructor to initialize a journal entry with given date, food name, calories, and note
    JournalEntry(const string& date, const string& foodName, double calories, const string& note)
        : date(date), foodName(foodName), calories(calories), note(note){}
};

class Journal {
private:
    string fileName;
    // Collection of journal entries
    vector<JournalEntry> entries;
public:
    // Default constructor
    Journal();
    // Construct the initializes a Journal by entries from a file
    Journal(const string &fileName);
    // Method to return current date
    static string getCurrentDate();
    // Method to add new entry to the journal with give food name, calories, and optional note
    void addEntry(const string& foodName, double calories, const string& note);
    // Method to display all entries in journal
    void displayEntries();
    // Method to save journal entries
    void saveToFile(const std::string &fileName) const;
    // Method to load all journal entries from a specified file
    void loadFromFile(const string& fileName);
    // Method to return the number of entries currently in the journal
    int getEntryCount() const;
};


#endif //CALORIETRACKER_JOURNAL_H
