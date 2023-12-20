#include "../store.h"
char* validateYesNo() {
    int sizeOfInput = 15;
    char* userAnswer = malloc(sizeOfInput * sizeof(char));
    while (1) {
        if (fgets(userAnswer, sizeOfInput, stdin) != NULL) {
            char *newline = strchr(userAnswer, '\n');
            if (newline != NULL) {
                *newline = '\0';  // Remove newline character
            } else {
                printf("Input too large\n");
                printf("Try again: ");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

            if (strcmp(userAnswer, "yes") == 0 || strcmp(userAnswer, "no") == 0) {
                return userAnswer;
            } else {
                printf("Invalid input %s, only accepts 'yes' and 'no'\n", userAnswer);
                printf("Try again: ");
            }

        }
    }
}
char* validateNumber(int length) {
    char* userAnswer = malloc(length + 1 * sizeof(char));
    while (1) {
        if (fgets(userAnswer, length + 2, stdin) != NULL) { // +2 to account for newline and null terminator
            char *newline = strchr(userAnswer, '\n');
            if (newline != NULL) {
                *newline = '\0';
            } else {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                printf("Input too large\n");
                printf("Try again: ");
                continue;
            }
            if (digitsOnly(userAnswer) && strlen(userAnswer) == length) {
                return userAnswer;
            } else {
                printf("Invalid input %s, only accepts numbers of length %d\n", userAnswer, length);
                printf("Try again: ");
            }
        }
    }
}
char* validatePrescription(int length) {
    char* userAnswer = malloc(length + 1 * sizeof(char));
    while (1) {
        if (fgets(userAnswer, length + 2, stdin) != NULL) { // +2 to account for newline and null terminator
            char *newline = strchr(userAnswer, '\n');
            if (newline != NULL) {
                *newline = '\0';
            } else {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                printf("Input too large\n");
                printf("Try again: ");
                continue;
            }

            if (digitsOnly(userAnswer) && strlen(userAnswer) == length || strcmp(userAnswer, "done") == 0 ) {
                printf("Answer accepted\n");
                return userAnswer;
            } else {
                printf("Invalid input %s, only accepts numbers of length %d or 'done'\n", userAnswer, length);
                printf("Try again: ");
            }
        }
    }
}