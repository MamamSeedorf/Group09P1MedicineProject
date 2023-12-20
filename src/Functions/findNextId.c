#include "../store.h"
int findNextId(FILE* file){
    int maxId = -1;

    if (file == NULL) {
        printf("File does not exist or cannot be opened.\n");
        return -1;
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        int tempLineId;
        if (sscanf(line, "%d,", &tempLineId) == 1) {
            if (tempLineId > maxId) {
                maxId = tempLineId;
            }
        }
    }

    return maxId + 1;

}