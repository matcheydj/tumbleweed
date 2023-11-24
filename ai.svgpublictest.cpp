// Please note this program is Case-specific in case the color names defined in the HTML5 specification for SVG do not adhere to the color input.
// Requires libcurl and JSON parsing or regular expression library to parse response. If you’re not familiar with these libraries or concepts, you might want to consult the documentation or seek help from a more experienced programmer.
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <curl/curl.h>
#include <vector>
#include <algorithm>

// Function to generate a random SVG file with a specified number of lines.
void generateSvgFile(int numLines, int width, int height, const std::string& color, const std::string& filename) {
    std::ofstream file(filename);

    // Write SVG header.
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" << width << "\" height=\"" << height << "\">\n";

    // Generate random lines.
    for (int i = 0; i < numLines; i++) {
        int x1 = std::rand() % width;
        int y1 = std::rand() % height;
        int x2 = std::rand() % width;
        int y2 = std::rand() % height;

        // Write line element with random coordinates.
        file << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2
             << "\" style=\"stroke:" << color << ";stroke-width:2\" />\n";
    }

    // Write SVG footer.
    file << "</svg>\n";

    // Close SVG file.
    file.close();
}

// Function to get the HTML color names from a web page.
std::vector<std::string> getColorNames() {
    // This is just a placeholder. In a real program, you would send a GET request to the web page and parse the response to extract the color names.
    return {"red", "green", "blue"};
}

int main() {
    // Initialize random number generator.
    std::srand(std::time(0));

    // Ask user to pick a number from 1-20 or "Surprise Me!".
    std::string input;
    std::cout << "Pick a number from 1-20 or enter 'Surprise Me!': ";
    std::cin >> input;

    int numLines;
    int width = 100;
    int height = 100;

    if (input == "Surprise Me!") {
        numLines = std::rand() % 20 + 1;  // Random number from 1-20.
        width = 16000;
        height = 24000;
    } else {
        numLines = std::stoi(input);

        // Validate user input.
        if (numLines < 1 || numLines > 20) {
            std::cout << "Invalid input. Please enter a number from 1-20.\n";
            return 1;
        }
    }

    // Get the HTML color names from a web page.
    std::vector<std::string> colorNames = getColorNames();

    // Ask user to specify the color of the lines.
    std::string color;
    std::cout << "Enter the color of the lines: ";
    std::cin >> color;

    // Check if the color is valid.
    if (std::find(colorNames.begin(), colorNames.end(), color) == colorNames.end()) {
        std::cout << "Invalid color. Please enter a valid HTML color name.\n";
        return 1;
    }

    // Generate SVG file.
    std::string filename = "output.svg";
    generateSvgFile(numLines, width, height, color, filename);

    // Create HTML file.
    std::ofstream htmlFile("output.html");

    // Write HTML header.
    htmlFile << "<!DOCTYPE html>\n<html>\n<head>\n<title>SVG Output</title>\n</head>\n<body>\n";

    // Include SVG file in HTML file.
    htmlFile << "<img src=\"" << filename << "\" alt=\"Random lines\">\n";

    // Write HTML footer.
    htmlFile << "</body>\n</html>\n";

    // Close HTML file.
    htmlFile.close();

    return 0;
}
// HTML follows. Review and use carefully.
<!DOCTYPE html>
<html>
<head>
    <title>SVG Line Generator</title>
    <script>
        function generateSvg() {
            // Get user input.
            var numLines = document.getElementById('numLines').value;
            var color = document.getElementById('color').value;

            // Validate color input by setting it as the background color of a hidden div.
            var colorDiv = document.getElementById('colorDiv');
            colorDiv.style.backgroundColor = color;
            if (colorDiv.style.backgroundColor === '') {
                alert('Invalid color. Please enter a valid HTML color name.');
                return;
            }

            // Generate SVG.
            var svg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
            svg.setAttribute('width', '100');
            svg.setAttribute('height', '100');

            for (var i = 0; i < numLines; i++) {
                var x1 = Math.random() * 100;
                var y1 = Math.random() * 100;
                var x2 = Math.random() * 100;
                var y2 = Math.random() * 100;

                var line = document.createElementNS('http://www.w3.org/2000/svg', 'line');
                line.setAttribute('x1', x1);
                line.setAttribute('y1', y1);
                line.setAttribute('x2', x2);
                line.setAttribute('y2', y2);
                line.setAttribute('style', 'stroke:' + color + ';stroke-width:2');

                svg.appendChild(line);
            }

            // Display SVG.
            var container = document.getElementById('container');
            container.innerHTML = '';
            container.appendChild(svg);
        }
    </script>
</head>
<body>
    <label for="numLines">Number of lines:</label>
    <input type="number" id="numLines" min="1" max="20">
    <br>
    <label for="color">Color:</label>
    <input type="text" id="color">
    <br>
    <button onclick="generateSvg()">Generate SVG</button>
    <div id="container"></div>
    <div id="colorDiv" style="display: none;"></div>
</body>
</html>
// In this HTML file, the user is asked to enter the number of lines and the color. When the user clicks the “Generate SVG” button, the generateSvg JavaScript function is called. This function gets the user’s input, validates the color input by setting it as the background color of a hidden div, generates an SVG element with the specified number of lines and color, and displays the SVG element in a div.
