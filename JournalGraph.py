import csv  
import matplotlib.pyplot as plt
from datetime import datetime
from collections import defaultdict

# Reads journal data from a CSV file and returns a list of (date, calories) 
def journalData(filename):
    entries = []
    try:
        with open(filename, 'r') as file:
            reader = csv.reader(file)
            for row in reader:
                if len(row) < 1:
                    continue
                try:
                    # Convert date to a datetime object
                    date = datetime.strptime(row[0], '%Y-%m-%d').date()
                    # Get calories from the third column
                    calories = float(row[2])
                    entries.append((date, calories))
                except ValueError:
                    continue
    except FileNotFoundError:
        print(f"File '{filename}' not found!")
    
    return entries

# Plots the total calories consumed per day from the journal entries
def plotCalories(entries):
    caloriesByDate = defaultdict(float)
    for entry in entries:
        date, calories = entry
        caloriesByDate[date] += calories

    # Extract dates and corresponding total calories for plotting
    dates = list(caloriesByDate.keys())
    totalCalories = list(caloriesByDate.values())


    ax = plt.subplot(111)
    ax.plot(dates, totalCalories, marker='o', linestyle='-', color='b', label='Total Calories')
    plt.gcf().canvas.manager.set_window_title('Calorie Tracker - Journal Data')
    plt.title('Total Calories Consumer Per Day')
    plt.xlabel('Date')
    plt.ylabel('Total Calories Consumed')
    plt.xticks(rotation=45)
    plt.grid(True)
    plt.tight_layout()

    plt.savefig('public/CaloriesOverTime.png')

if __name__ == "__main__":
    filename = "cmake-build-debug/Journal.csv"
    journal_entries = journalData(filename)
    if journal_entries:
        plotCalories(journal_entries)
    else:
        print("No valid journal entries found to plot.")