#include <iostream>
#include <vector>
#include <string>

class Rumor {
private:
    std::string content;
    bool isTrue;

public:
    Rumor(std::string content) : content(content), isTrue(false) {}

    void checkRumor() {
        char choice;
        std::cout << "Is the rumor '" << content << "' true or false? Enter T for true or F for false: ";
        std::cin >> choice;

        if (choice == 'T' || choice == 't') {
            isTrue = true;
        } else if (choice == 'F' || choice == 'f') {
            isTrue = false;
        } else {
            std::cout << "Invalid input. Please enter T or F.\n";
        }
    }

    bool getIsTrue() {
        return isTrue;
    }
};

int main() {
    std::vector<Rumor> rumors;
    int trueCount = 0;

    for (int i = 0; i < 10; i++) {
        std::string rumorContent;
        std::cout << "Enter rumor " << (i + 1) << ": ";
        std::getline(std::cin, rumorContent);

        Rumor rumor(rumorContent);
        rumors.push_back(rumor);
    }

    for (Rumor &rumor : rumors) {
        rumor.checkRumor();
        if (rumor.getIsTrue()) {
            trueCount++;
        }
    }

    double truePercentage = (double)trueCount / rumors.size() * 100;
    double falsePercentage = 100 - truePercentage;

    std::cout << "\nHere are the results:\n";
    std::cout << "Percentage of rumors that are true: " << truePercentage << "%\n";
    std::cout << "Percentage of rumors that are false: " << falsePercentage << "%\n";

    return 0;
}
// This program will prompt the user to enter the content of up to 10 rumors. Each rumor is stored as an instance of the Rumor class, which is then added to a vector of rumors. After all rumors have been entered, the program will prompt the user to enter whether each rumor is true or false. If the user enters ‘T’ or ‘t’, the rumor is marked as true. If the user enters ‘F’ or ‘f’, the rumor is marked as false. If the user enters any other character, the program will output “Invalid input. Please enter T or F.” After all rumors have been checked, the program will calculate and output the percentage of rumors that are true and false. Please note that this program does not validate the input beyond checking for ‘T’ or ‘F’. If the user enters more than one character, only the first character will be considered. Also, the program is case-insensitive, meaning it treats ‘T’ and ‘t’ (or ‘F’ and ‘f’) as the same.
