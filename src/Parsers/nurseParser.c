#include "../store.h"

int parseUser(char *line, Nurse *nurse) {
    char *token;
    char *rest = line;
    int comboIndex = 0;

    nurse->id = parseInt(&token, &rest);
    if (token == NULL) return 0;

    parseString(&token, &rest, nurse->username, MAX_NAME_PARSER);
    if (token == NULL) return 0;

    parseString(&token, &rest, nurse->password, MAX_NAME_PARSER);
    if (token == NULL) return 0;

    return 1;
}