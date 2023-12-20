#include "../store.h"

int parseInt(char **token, char **rest) {
    *token = strtok_r(*rest, ",", rest);
    if (*token != NULL) {
        return atoi(*token);
    } else {
        return -1;
    }
}

long long parseLongLongInt(char **token, char **rest) {
    *token = strtok_r(*rest, ",", rest);
    if (*token != NULL) {
        return atoll(*token);
    } else {
        return -1;
    }
}

void parseString(char **token, char **rest, char *output, int maxLen) {
    *token = strtok_r(*rest, ",", rest);
    if (*token != NULL) {
        strncpy(output, *token, maxLen);
        output[maxLen - 1] = '\0'; // Ensure null-termination
    }
}

int parseArray(char **token, char **rest, long long int *array) {
    char *innerRest;
    char *comboToken;
    int index = 0;

    *token = strtok_r(*rest, ",", rest);
    comboToken = strtok_r(*token, "[;]", &innerRest);

    while (comboToken != NULL) {
        if (comboToken[0] != '\0') {
            array[index] = atoll(comboToken);
            index++;
        }
        comboToken = strtok_r(NULL, "[;]", &innerRest);
    }

    return index;
}