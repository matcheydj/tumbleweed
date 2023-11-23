#include <fstream>
#include <cstdlib>
#include <ctime>

// This program will prompt the user to enter a number from 1-5. It will then generate that many SVG files, each with a number of lines equal to the user’s input. The coordinates of the lines are determined by random numbers. The program will also create an HTML file that includes these SVG files using the <img> tag. The SVG and HTML files will be saved in the same directory as the program. The user can open the HTML file in a web browser to view the SVG images.
// Function to generate a random SVG file with a specified number of lines.
void generateSvgFile(int numLines, const std::string& filename) {
    std::ofstream file(filename);

    // Write SVG header.
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"100\" height=\"100\">\n";

    // Generate random lines.
    for (int i = 0; i < numLines; i++) {
        int x1 = std::rand() % 100;
        int y1 = std::rand() % 100;
        int x2 = std::rand() % 100;
        int y2 = std::rand() % 100;

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

    // Generate SVG files.
    for (int i = 0; i < numLines; i++) {
        std::string filename = "output" + std::to_string(i + 1) + ".svg";
        generateSvgFile(numLines, filename);
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
// Sure, here’s a simple C++ program that asks a user to pick a number from 1-5, then creates SVG files with random lines based on the user’s input. It also creates an HTML file that displays these SVG files.
// This program uses the C++ Standard Library for file I/O and random number generation. It does not use any third-party libraries or platform-specific code, so it should work on any system with a C++ compiler and standard library.
