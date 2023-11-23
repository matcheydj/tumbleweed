// In this modified version of the program, the user is asked to enter the width and height of the SVG images after choosing the number of lines. These dimensions are then passed to the generateSvgFile function, which uses them to set the size of the SVG images and to generate the random coordinates for the lines.
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

    // Ask user to pick a number from 1-5.
    int numLines;
    std::cout << "Pick a number from 1-5: ";
    std::cin >> numLines;

    // Validate user input.
    if (numLines < 1 || numLines > 5) {
        std::cout << "Invalid input. Please enter a number from 1-5.\n";
        return 1;
    }

    // Ask user to specify the size of the SVG images.
    int width, height;
    std::cout << "Enter the width of the SVG images: ";
    std::cin >> width;
    std::cout << "Enter the height of the SVG images: ";
    std::cin >> height;

    // Generate SVG files.
    for (int i = 0; i < numLines; i++) {
        std::string filename = "output" + std::to_string(i + 1) + ".svg";
        generateSvgFile(numLines, width, height, filename);
    }

    // Create HTML file.
    std::ofstream htmlFile("output.html");

    // Write HTML header.
    htmlFile << "<!DOCTYPE html>\n<html>\n<head>\n<title>SVG Output</title>\n</head>\n<body>\n";

    // Include SVG files in HTML file.
    for (int i = 0; i < numLines; i++) {
        std::string filename = "output" + std::to_string(i + 1) + ".svg";
        htmlFile << "<img src=\"" << filename << "\" alt=\"Random lines\">\n";
    }

    // Write HTML footer.
    htmlFile << "</body>\n</html>\n";

    // Close HTML file.
    htmlFile.close();

    return 0;
}
