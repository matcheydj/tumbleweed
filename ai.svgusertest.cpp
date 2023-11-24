// User test has been modified to allow user to specify color
// User is asked to specify after choosing a number for lines
#include <fstream>
#include <cstdlib>
#include <ctime>

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

    // Ask user to specify the color of the lines.
    std::string color;
    std::cout << "Enter the color of the lines: ";
    std::cin >> color;

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
// The user must also have permission to read the SVG and HTML files and must know how to open the HTML file in a web browser. If the user is not familiar with these technologies, you might need to provide additional instructions or assistance.
