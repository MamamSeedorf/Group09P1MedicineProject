#include "../store.h"
#include <string.h>



int parseMedicine(char *line, Medicine *med) {
    char *token;
    char *rest = line;

    med->id = parseInt(&token, &rest);
    if (token == NULL) return 0;

    med->ndc = parseLongLongInt(&token, &rest);
    if (token == NULL) return 0;

    parseString(&token, &rest, med->name, MAX_NAME_PARSER);
    if (token == NULL) return 0;

    parseString(&token, &rest, med->description, MAX_NAME_PARSER);
    if (token == NULL) return 0;

    med->numberOfInteractionRisks = parseArray(&token, &rest, med->interactionRisks);

    parseString(&token, &rest, med->typicalDosage, MAX_NAME_PARSER);
    if (token == NULL) return 0;


    return 1;
}