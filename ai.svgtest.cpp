// In ln this modified version of the program, the user is asked to enter a number from 1-20 or “Surprise Me!”. If the user enters “Surprise Me!”, the program generates a random number of lines and sets the size of the SVG image to 16000x24000. If the user enters a number, the program uses that number of lines and the default size of 100x100.
#include <fstream>
#include <cstdlib>
#include <ctime>

// Function to generate a random SVG file with a specified number of lines.
void generateSvgFile(int numLines, int width, int height, const std::string& filename) {
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
             << "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n";
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

    // Generate SVG file.
    std::string filename = "output.svg";
    generateSvgFile(numLines, width, height, filename);

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
// Good luck DP: The user can open the HTML file in a web browser to view the SVG image, which will now have the size and number of lines specified by the user.
// If you’re including the SVG files in an HTML page, you should sanitize the output to prevent cross-site scripting attacks. Finally, please note that this program generates very simple SVG files with only lines. If you need to generate more complex SVG graphics, you might want to use a dedicated SVG library or a graphics library that supports SVG output.
// If you need to create more complex HTML pages, you might want to use a dedicated HTML library or a web development framework. If you need to interact with the user in a more complex way, such as responding to user events or updating the page dynamically, you might want to use #JavaScript in addition to HTML and SVG.
