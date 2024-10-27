# M3OEP-msteenbe
### Mitchell Steenbergen
### Installation
* Required
  * C++ Compiler: MinGW
  * CMake: https://cmake.org/download/ 
  * Python
  * matplotlib: pip install matplotlib
  * Node.js: https://nodejs.org/en 

### Project Summary
My project is a Calorie Tracker program. It is now a multi-language project, which allows users to track their calorie intake through web-based interaction. It allows user to:
 * Add food and their calorie values per grams (only in grams) All units are converted to grams
 * Maintain a journal of daily food entries, including calories consumed and optional notes
 * Calculate total calories based on food weight (only in grams)
 * Search and filter foods by name, calories or both
 * Display Journal Entries
 * Remove foods from the database
### Program Languages
My program starts in __JavaScript__, specifically using Node.js for a server-side logic. It then uses __HTML__ and __CSS__ for the website with a user interface built in. Once the user interacts with the site __C++__ is used to perform the calculations, and the food managment. And __python__ is used for visualization of calorie consumption. 

### Use of Languages
In my program __JavaScript__ is used for server-side logic, it handles the interactions between the web interface and the backend. Between Html and C++. For me, it offered flexibility with integrating with other languages specfically C++. And you can use it on frontend and backend. __HTML__ and __CSS__ are used to create the structure and style of the website/user interface. Html is a fundmental language in web development. It's the building blocks, the structure. CSS is great because it allows you to define styles of a website/page. Create visually pleasing designs and whatnot. __C++__ is used for calculations and managing the food database. It's ideal because it's very efficient when handling data and calculations. __Python__ is used to create a graph. It's great for that because it has libraries that are made to handle visualization, like Matplotlib. 

### How Languages are Connected
HTML interacts with JavaScript through form submissions using the POST method. For example: <form action="/displayEntries" method="POST"> sends data to the server, which is handled by Node.js in the server.js file. In the server code, the route app.post('/displayEntries', (req, res) => { ... } captures this request and processes it. The form action and any input data/arguments. Once the JavaScript receives it, it constructs a command, such as const command = 'CalorieTracker displayEntries';, which starts the C++ program and passes the arguments. C++ takes those arguments and processes them to a corresponding piece of code like: else if (action == "displayEntries") { journal.displayEntries(); }. And other code like this will run the calculations or operations. 

The C++ program sends output back to JavaScript using standard output (cout) with HTML formatting, for example: cout << "<a class='back-link' href='/'>Go Back to Main Page</a>\n"; which this adds a link to return to the main webpage. This is captured by JavaScript, which then creates a new webpage to display the results. And this cout does technically make C++ resposible for some html. Python is invoked by both JavaScript and C++ through commands in both code, like in c++: system("py JournalGraph.py"); CSS is linked to HTML through these: <link rel="stylesheet" href="styles.css"> and C++ through these: cout << "<link rel='stylesheet' href='cpp.css'>\n"; These ensure consistent styling throughout the program. 

### Known Bugs
* No known bugs 

### Future Work 
* Enhanced Data Visualization: Expand the graphing feature to include more types of visualization. Maybe an interactive dashboard. 
* Nutritional Information: Extend the food database to include the macros of each food. 
* Recipe: Perhaps to add a way for them to get recipes that's within their specified calorie limit from foods they input.

### Citations
* https://www.geeksforgeeks.org/command-line-arguments-in-cpp/ 
* https://www.youtube.com/watch?v=zivkHZ9w7DY 
* https://www.w3schools.com/html/html_css.asp   

### Grade
* Main Program (Great - 40 pts):
  * The main program uses concepts from Module 3, including multi-language integration. With server-side interaction. It is highly interactive, allowing users to add food items, manage a journal, calculate calories, search for foods, and visualize data through graphs. It has user input validation. Also has I think effective integration of JavaScript, C++, Python, HTML, and CSS. 
* Use of Multiple Languages (Great - 20 pts):
  * The program integrates multiple languages effectively. JavaScript (Node.js) for server-side, C++ for backend computations, Python for visualization, and HTML/CSS for frontend design. The extensive use of JavaScript, C++, HTML/CSS each have a significant amount of work (python is just there, not much going on in that file) and I think they are well integrated together. 
* Choice of Languages (Great - 20 pts):
  * JavaScript (Node.js): Excellent choice for server-side logic, as it allows ease of integration with other languages. C++: Ideal for performing calculations and handling data due to its efficienty, making it well suited for that. Python: Great for visualization of data, as it has powerful libraries like Matplotlib to generate graphs. HTML/CSS: Both used in the structure and style/design of the website/webpage. HTML is an ideal choice because it is like the building blocks or the structure for web development. It provides a foundation for structuring content in a clear way. CSS is great for styling, defining styles for you website/page. And it allows for seamless integration with HTML.  
* Command Line or File I/O (Great - 20 pts):
  * The program features the passing of data between languages by using command line arguments. Take command line arugments, the HTML collects information from the web interface and passes that to server.js which then passes those arguments to C++ through command line arguments. 