#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_COUNT 16
#define CHOICE_COUNT 5

// Helper functions
void free_string(char *str) {
  if (str) {
    free(str);
  }
}

char *join_words(const char *word1, const char *word2, const char *word3) {
  int total_length = strlen(word1) + strlen(word2) + strlen(word3) + 3;
  char *joined = malloc(total_length * sizeof(char));

  if (!joined) {
    return NULL;
  }

  sprintf(joined, "%s %s %s", word1, word2, word3);
  return joined;
}

void shuffle_array(char **array, int size) {
  for (int i = 0; i < size; i++) {
    int j = rand() % size;
    char *temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
}

// Main functions
char *random_word(int n) {
  char *word = malloc((n + 1) * sizeof(char));
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

  if (!word) {
    return NULL;
  }

  for (int i = 0; i < n; i++) {
    int r = rand() % 26;
    word[i] = alphabet[r];
  }
  word[n] = '\0';
  return word;
}

char **random_list(int m) {
  char **list = malloc(m * sizeof(char *));

  if (!list) {
    return NULL;
  }

  for (int i = 0; i < m; i++) {
    int n = rand() % 10 + 1;
    list[i] = random_word(n);

    if (!list[i]) {
      // Free allocated memory for previous words on error
      for (int j = 0; j < i; j++) {
        free_string(list[j]);
      }
      free(list);
      return NULL;
    }
  }
  return list;
}

void create_button(const char *label) {
  printf("<button onclick=\"select(this)\">%s</button>\n", label);
}

void create_text(const char *content) {
  printf("<text x=\"50%%\" y=\"50%%\" text-anchor=\"middle\" alignment-baseline=\"middle\" font-size=\"32\">%s</text>\n", content);
}

// User interaction
char **choices;
int current_choice = 0;

void select(char *button_label) {
  if (current_choice < CHOICE_COUNT) {
    choices[current_choice] = button_label;
    current_choice++;

    if (current_choice == CHOICE_COUNT) {
      display_choices();
    }
  }
}

void display_choices() {
  printf("<svg width=\"100%%\" height=\"100%%\" viewBox=\"0 0 100 100\">\n");

  for (int i = 0; i < CHOICE_COUNT; i++) {
    create_text(choices[i]);
    printf("<animateTransform attributeName=\"transform\" type=\"translate\" from=\"0 0\" to=\"0 %d\" dur=\"1s\" fill=\"freeze\"/>\n", (i - 2) * 20);
  }

  printf("</svg>\n");
}

int main() {
  srand(time(NULL));
  char **list = random_list(WORD_COUNT);

  if (!list) {
    return 1;
  }

  choices = malloc(CHOICE_COUNT * sizeof(char *));

  if (!choices) {
    free(list);
    return 1;
  }

  printf("<!DOCTYPE html>\n");
  printf("<html>\n");
  printf("<head>\n");
  printf("<script>\n");
  printf("%s\n", select);
  printf("</script>\n");
  printf("</head
