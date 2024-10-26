import csv  
import matplotlib.pyplot as plt
from datetime import datetime

def journalData(filename):
    entries = []
    try:
        with open(filename, 'r') as file:
            reader = csv.reader(file)
            for row in reader:
                if len(row) < 1:
                    continue
                try:
                    date = datetime.strptime(row[0], '%Y-%m-%d')
                    calories = float(row[2])
                    entries.append((date, calories))
                except ValueError:
                    continue
    except FileNotFoundError:
        print(f"File '{filename}' not found!")
    
    return entries

def plotCalories(entries):
    entries.sort(key=lambda x: x[0])

    dates = [entry[0] for entry in entries]
    calories = [entry[1] for entry in entries]


    ax = plt.subplot(111)
    ax.plot(dates, calories, marker='o', linestyle='-', color='b', label='Calories')
    plt.gcf().canvas.manager.set_window_title('Calorie Tracker - Journal Data')
    plt.title('Calories Consumed Over Time')
    plt.xlabel('Date')
    plt.ylabel('Calories Consumed')
    plt.xticks(rotation=45)
    plt.grid(True)
    plt.tight_layout()

    # Save the graph to a file
    plt.savefig('public/CaloriesOverTime.png')

if __name__ == "__main__":
    filename = "cmake-build-debug/Journal.csv"
    journal_entries = journalData(filename)
    if journal_entries:
        plotCalories(journal_entries)
    else:
        print("No valid journal entries found to plot.")