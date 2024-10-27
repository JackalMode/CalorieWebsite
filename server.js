const express = require('express');
const { exec } = require('child_process');
const path = require('path');

const app = express();
const PORT = 3000;
console.log("Server started")
app.use(express.static('public'));
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

// Route for the main page, serving 'index.html'
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Route to handle calorie calculation request
app.post('/calculate', (req, res) => {
    const { foodName, weight } = req.body;
     // The command to run the C++ program to calculate calories
    const command = `CalorieTracker calcCalories "${foodName}" ${weight}`;

    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing command: ${error.message}`);
            res.status(500).send(`Error: ${stderr || error.message}`);
        } else {
            res.send(stdout);
        }
    });
});
// Route to add food to the database
app.post('/add', (req, res) => {
    const { foodName, caloriesPer100g } = req.body;
    // The command to run the C++ program to Add Food
    const command = `CalorieTracker addFood "${foodName}" ${caloriesPer100g}`;

    exec(command, (error, stdout, stderr) => {
        if(error){
            res.status(500).send(`Error: ${stderr}`);
        } else {
            res.send(stdout);
        }
    });
});
// Route to remove food from the database
app.post('/remove', (req, res) => {
    const { foodName } = req.body;
    // The command to run the C++ program to Remove Food
    const command = `CalorieTracker removeFood "${foodName}"`;

    exec(command, (error, stdout, stderr) => {
        if(error){
            res.status(500).send(`Error: ${stderr}`);
        } else {
            res.send(stdout);
        }
    });
});
// Route to search for food based on different criteria
app.post('/search', (req, res) => {
    const { searchType, searchTerm, calories, showLess } = req.body;
    let command = `CalorieTracker`;

    // Determine the command based on the search type.
    if(searchType === 'name'){
        command += ` searchFoodByName "${searchTerm}"`;
    } else if (searchType === 'calories') {
        command += ` displayByCalories ${calories} ${showLess}`;
    } else if (searchType === 'both') {
        command += ` searchByBoth "${searchTerm}" ${calories} ${showLess}`;
    }
    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing command: ${error.message}`);
            res.status(500).send(`Error: ${stderr || error.message}`);
        } else {
            res.send(stdout);
        }
    });
});
// Route to generate a graph of journal entries
app.post('/generateGraph', (req, res) => {
    const command = `py JournalGraph.py`;

    exec(command, (error, stdout, stderr) => {
        if (error) {
            res.status(500).send(`Error: ${stderr}`);
        } else {
            res.sendFile(path.join(__dirname, 'public', 'displayGraph.html'));
        }
    });
});
// Route to add an entry to the journal
app.post('/addToJournal', (req, res) => {
    const { foodName, weight, note } = req.body;
    // The command to run the C++ program to Add to Journal
    const command = `CalorieTracker addToJournal "${foodName}" ${weight} "${note}"`;
    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing command: ${error.message}`);
            res.status(500).send(`Error: ${stderr}`);
        } else {
            res.send(stdout);
        }
    });
    
});
// Route to display all journal entries
app.post('/displayEntries', (req, res) => {
    // The command to run the C++ program to Display Entries
    const command = `CalorieTracker displayEntries`;

    exec(command, (error, stdout, stderr) => {
        if (error) {
            res.status(500).send(`Error: ${stderr}`);
        } else {
            res.send(stdout);
        }
    });
});
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

