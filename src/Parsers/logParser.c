#include "../store.h"

int parseLog(char *line,LogEntry *log) {
    char *token;
    char *rest = line;

    log->id = parseInt(&token, &rest);
    if (token == NULL) return 0;

    parseString(&token, &rest, log->description, MAX_DESCRIPTION);
    if (token == NULL) return 0;

    log->userID = parseInt(&token, &rest);
    if (token == NULL) return 0;


    parseString(&token, &rest, log->date, MAX_NAME_PARSER);
    if (token == NULL) return 0;

    return 1;
}