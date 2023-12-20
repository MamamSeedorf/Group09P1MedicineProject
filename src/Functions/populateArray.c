#include "../store.h"


int populatePatientArray(FILE* file, Patient* patientArray) {
    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_MEDCINES) {
        if (parsePatient(line, &patientArray[count])) {
            count++;
        }
    }

    return count;
}
int populateMedicineArray(FILE* file, Medicine* medicineArray) {
    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_MEDCINES) {
        if (parseMedicine(line, &medicineArray[count])) {
            count++;
        }
    }

    return count;
}

int populateLogArray(FILE* file, LogEntry* logArray) {
    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_MEDCINES) {
        if (parseLog(line, &logArray[count])) {
            count++;
        }
    }

    return count;
}

long long int** allocateInteractionPair() {
    long long int** badInteractionPair = (long long int**)malloc(MAX_MEDCINES * sizeof(long long int*));

    if (badInteractionPair == NULL) {
        perror("MEMORY ALLOCATION FAILED");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_MEDCINES / 2; i++) {
        badInteractionPair[i] = (long long int*)malloc(2 * sizeof(long long int));
        if (badInteractionPair[i] == NULL) {
            perror("MEMORY ALLOCATION FAILED");
            for (int j = 0; j < i; j++) {
                free(badInteractionPair[j]);
            }
            free(badInteractionPair);
            exit(EXIT_FAILURE);
        }
    }

    return badInteractionPair;
}
