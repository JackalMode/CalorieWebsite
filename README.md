# M2OEP-msteenbe
### Mitchell Steenbergen
### Project Summary
My project is a Calorie Tracker program which allows users to track their calorie intake. It allows user to:
 * Add food and their calorie values per grams, ounces, or pounds. All units are converted to grams
 * Maintain a journal of daily food entries, including calories consumed and optional notes
 * Calculate total calories based on food weight in either grams, ounces, or pounds
 * Search and filter foods by name, calories or both
 * Display Journal Entries
 * Remove foods from the database

### Concepts Used
* Component Class Relationship
  * The `FoodDatabase` class holds a vector of `Food` objects, creating a composition relationship between classes
  * The `Menu` class interacts with `FoodDatabase` and `Journal`. And uses a `FoodDatabase` reference to interact with food items.
  * The `Journal` class contains a vector of `JournalEntry` objects. So the`Journal` "has" `JournalEntry` groups. Representing a "has-a" relationship
* File input/output
    * The `Journal` class handles saving, loading, adding, and displaying entries to/from a CSV file. 
    * The `FoodDatabase` class handles saving, loading, adding, displaying, and removing food to/from a CSV file. 
### Known Bugs
* No known bugs found yet

### Future Work 
* Website: I plan to expand the program to a web-based version
* Graphs: I plan to add graphs to show the amount calories eaten over a certain period of time. 
* Nutritional Information: Extend the food database to include the macros of each food. 
* Recipe: Perhaps to add a way for them to get recipes that's within their specified calorie limit from foods they input.

### Citations
* https://www.geeksforgeeks.org/transform-c-stl-perform-operation-elements/
* https://www.geeksforgeeks.org/push_back-vs-emplace_back-in-cpp-stl-vectors/
* https://en.cppreference.com/w/cpp/chrono/year_month_day
* https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c

### Grade
* Main Program (Great - 40 pts):
  * The main program is interactive and uses module 2 concepts. It has input validation that is correctly implemented through all classes. The code is well-designed with minimal code in the `main` function, making it easy to add or remove features and build upon 
* Testing Program (Great - 20 pts):
  * The testing program is organized into functions and has multiple test cases for each non-trivial method. It thoroughly tests all major functionalities. However, the `Menu` class is not in the `Test.cpp` as it primarily handles user interaction, which is difficult test. And the `Menu` class relies heavily on methods from other classes, which are already being tested individually.  
* Concepts: Component Class Relationship (Great - 20 pts):
  * The class relationships (`Journal` with `JournalEntry`, `Menu` with `FoodDatabase` and `Journal`) are designed well, implemented robustly, and used effectively in the main program to create a cohesive functionality.
* Concepts: File Input/Output (Good - 10 pts):
  * The use of file input/output in `FoodDatabase` and `Journal` classes is well-designed and implemented robustly to read, write, and manage food and journal entries in CSV files.