const express = require('express');
const { exec } = require('child_process');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(express.static('public'));
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.post('/calculate', (req, res) => {
    const { foodName, weight } = req.body;
    const command = `CalorieTracker.exe calcCalories ${foodName} ${weight}`;

    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing command: ${error.message}`);
            res.status(500).send(`Error: ${stderr || error.message}`);
        } else {
            res.send(stdout);
        }
    });
});

app.post('/add', (req, res) => {
    const { foodName, caloriesPer100g } = req.body;
    const command = `CalorieTracker addFood ${foodName} ${caloriesPer100g}`;

    exec(command, (error, stdout, stderr) => {
        if(error){
            res.status(500).send(`Error: ${stderr}`);
        } else {
            res.send(stdout);
        }
    });
});

app.post('/remove', (req, res) => {
    const { foodName } = req.body;
    const command = `CalorieTracker removeFood ${foodName}`;

    exec(command, (error, stdout, stderr) => {
        if(error){
            res.status(500).send(`Error: ${stderr}`);
        } else {
            res.send(stdout);
        }
    });
});

app.post('/search', (req, res) => {
    const { searchType, searchTerm, calories, showLess } = req.body;
    let command = `CalorieTracker`;

    if(searchType == 'name'){
        command += ` searchFoodByName ${searchTerm}`;
    } else if (searchType == 'calories'){
        command += ` displayByCalories ${calories} ${showLess}`;
    } else if (searchType == 'both'){
        command += ` searchByFoodAndCalories ${searchTerm} ${calories} ${showLess}`;
    }
    
    exec(command, (error, stdout, stderr) => {
        if(error){
            res.status(500).send(`Error: ${stderr}`);
        } else {
            res.send(stdout);
        }
    });
});

app.post('/generateGraph', (req, res) => {
    const command = `py JournalGraph.py`;

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

