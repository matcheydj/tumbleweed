#include <iostream>

int main() {
    char rumor;
    std::cout << "Enter T if the rumor is true or F if it's false: ";
    std::cin >> rumor;

    if (rumor == 'T' || rumor == 't') {
        std::cout << "The rumor is true.\n";
    } else if (rumor == 'F' || rumor == 'f') {
        std::cout << "The rumor is false.\n";
    } else {
        std::cout << "Invalid input. Please enter T or F.\n";
    }

    return 0;
}
