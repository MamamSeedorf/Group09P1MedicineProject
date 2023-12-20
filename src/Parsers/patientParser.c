#include "../store.h"

int parsePatient(char *line, Patient *patient) {
    char *token;
    char *rest = line;

    patient->id = parseInt(&token, &rest);
    if (token == NULL) return 0;

    patient->ssn = parseLongLongInt(&token, &rest);
    if (token == NULL) return 0;

    parseString(&token, &rest, patient->name, MAX_NAME_PARSER);
    if (token == NULL) return 0;

    patient->numberofprescriptions = parseArray(&token, &rest, patient->prescriptions);
    if (patient->numberofprescriptions == -1) return 0;

    patient->numberofallergies = parseArray(&token, &rest, patient->allergies) - 1;
    if (patient->numberofallergies == -1) return 0;

    return 1;
}