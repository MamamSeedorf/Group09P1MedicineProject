
#include "../store.h"

void readMedicine(){
    FILE *file = openMedicineFileRead();
    char line[MAX_LINE_LENGTH];
    Medicine* medcineArray = (Medicine*)malloc(MAX_MEDCINES * sizeof(Medicine));
    int count = populateMedicineArray(file, medcineArray);


    fclose(file);
    for (int i = 0; i < count; i++) {
        printf("Id of medicine: %d\nName of medicine: %s\n\n", medcineArray[i].id, medcineArray[i].name);
    }
}
