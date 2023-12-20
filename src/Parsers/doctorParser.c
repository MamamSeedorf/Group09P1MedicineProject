#include "../store.h"

int parseAdmin(char *line, Doctor *doctor) {
    char *token;
    char *rest = line;

    doctor->id = parseInt(&token, &rest);
    if (token == NULL) return 0;

    parseString(&token, &rest, doctor->username, MAX_NAME_PARSER);
    if (token == NULL) return 0;

    parseString(&token, &rest, doctor->password, MAX_NAME_PARSER);
    if (token == NULL) return 0;

    return 1;
}