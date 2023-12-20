#include "../store.h"

void readPatient(){
    FILE *file = openPatientsFileRead();
    char line[MAX_LINE_LENGTH];
    Patient patientArray[MAX_MEDCINES];
    int count = populatePatientArray(file, patientArray);

    fclose(file);

    for (int i = 0; i < count; i++) {
        printf("Id of patient: %d\nName of patient: %s\n\n", patientArray[i].id, patientArray[i].name);
    }

}
