// I have written a program in C that creates a web page that has a background scripted element that generates and stores as a vector a random list of words, store the words in an array, and output the selections as 16 separate buttons on the webpage, each button containing at least 3 of those many words to the user. The program will make the users choose up to 5 of a total of 16 (up to 5 out of 16 choices) and put their choices in a second table array, and using vectors display them as text, generated as svg drawn as close to how the letters appear on an interactive web page. Here is the code:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// A function to generate a random word of length n
char* random_word(int n) {
    char* word = (char*)malloc(n+1); // Allocate memory for the word
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz"; // Define the alphabet
    for (int i = 0; i < n; i++) {
        int r = rand() % 26; // Generate a random index
        word[i] = alphabet[r]; // Assign a random letter
    }
    word[n] = '\0'; // Add the null terminator
    return word; // Return the word
}

// A function to generate a random list of words of size m
char** random_list(int m) {
    char** list = (char**)malloc(m * sizeof(char*)); // Allocate memory for the list
    for (int i = 0; i < m; i++) {
        int n = rand() % 10 + 1; // Generate a random word length between 1 and 10
        list[i] = random_word(n); // Generate a random word and add it to the list
    }
    return list; // Return the list
}

// A function to create a button with a label
void create_button(char* label) {
    printf("<button onclick=\"select(this)\">%s</button>\n", label); // Print the HTML code for the button
}

// A function to create a text element with a content
void create_text(char* content) {
    printf("<text x=\"50%%\" y=\"50%%\" text-anchor=\"middle\" alignment-baseline=\"middle\" font-size=\"32\">%s</text>\n", content); // Print the SVG code for the text
}

// A function to join three words with spaces
char* join_words(char* word1, char* word2, char* word3) {
    int n1 = strlen(word1); // Get the length of the first word
    int n2 = strlen(word2); // Get the length of the second word
    int n3 = strlen(word3); // Get the length of the third word
    int n = n1 + n2 + n3 + 3; // Get the total length of the joined words
    char* joined = (char*)malloc(n); // Allocate memory for the joined words
    sprintf(joined, "%s %s %s", word1, word2, word3); // Format the joined words
    return joined; // Return the joined words
}

// A function to shuffle an array of strings
void shuffle(char** array, int size) {
    for (int i = 0; i < size; i++) {
        int j = rand() % size; // Generate a random index
        char* temp = array[i]; // Swap the elements at i and j
        array[i] = array[j];
        array[j] = temp;
    }
}

// A global variable to store the user's choices
char** choices;
int choice_count = 0;

// A function to handle the user's selection of a button
void select(char* button) {
    if (choice_count < 5) { // If the user has not selected 5 buttons yet
        choices[choice_count] = button; // Add the button's label to the choices array
        choice_count++; // Increment the choice count
        button.disabled = true; // Disable the button
        if (choice_count == 5) { // If the user has selected 5 buttons
            display_choices(); // Display the choices as text
        }
    }
}

// A function to display the user's choices as text
void display_choices() {
    printf("<svg width=\"100%%\" height=\"100%%\" viewBox=\"0 0 100 100\">\n"); // Print the SVG tag
    for (int i = 0; i < 5; i++) { // For each choice
        create_text(choices[i]); // Create a text element with the choice
        printf("<animateTransform attributeName=\"transform\" type=\"translate\" from=\"0 0\" to=\"0 %d\" dur=\"1s\" fill=\"freeze\"/>\n", (i - 2) * 20); // Animate the text to move vertically
    }
    printf("</svg>\n"); // Print the closing SVG tag
}

int main() {
    srand(time(NULL)); // Initialize the random seed
    char** list = random_list(16); // Generate a random list of 16 words
    choices = (char**)malloc(5 * sizeof(char*)); // Allocate memory for the choices array
    printf("<!DOCTYPE html>\n"); // Print the HTML declaration
    printf("<html>\n"); // Print the HTML tag
    printf("<head>\n"); // Print the head tag
    printf("<script>\n"); // Print the script tag
    printf("%s\n", select); // Print the C code for the select function as JavaScript
    printf("</script>\n"); // Print the closing script tag
    printf("</head>\n"); // Print the closing head tag
    printf("<body>\n"); // Print the body tag
    shuffle(list, 16); // Shuffle the list of words
    for (int i = 0; i < 4; i++) { // For each row of buttons
        for (int j = 0; j < 4; j++) { // For each column of buttons
            int k = i * 4 + j; // Get the index of the word
            char* label = join_words(list[k], list[(k+1)%16], list[(k+2)%16]); // Join three words as the label
            create_button(label); // Create a button with the label
        }
        printf("<br>\n"); // Print a line break
    }
    printf("</body>\n"); // Print the closing body tag
    printf("</html>\n"); // Print the closing HTML tag
    return 0; // Return 0
}
