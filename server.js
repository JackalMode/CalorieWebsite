const express = require('express');
const { exec } = require('child_process');
const app = express();

app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});

app.post('/calculate', (req, res) => {
    const foodName = req.body.foodName;
    const weight = req.body.weight;

    if (!foodName || !weight) {
        return res.status(400).send("Food name and weight are required.");
    }

    const command = `calorie_calculator ${foodName} ${weight}`;
    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
            return res.status(500).send("An error occurred while calculating calories.");
        }
        res.send(`<h2>Result:</h2><p>${stdout}</p>`);
    });
});

app.listen(3000, () => {
    console.log('Server is running on port 3000');
});