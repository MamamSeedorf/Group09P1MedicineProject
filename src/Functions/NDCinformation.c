#include "../store.h"

void NdcInformation() {
    FILE *file = openMedicineFileRead();

    char line[MAX_LINE_LENGTH];
    Medicine * medicineArray = (Medicine *)malloc(MAX_MEDCINES * sizeof(Medicine));
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (parseMedicine(line, &medicineArray[count])) {
            count++;
        }
    }

    fclose(file);

    long long int ndc;
    printf("Enter the NDC of the medicine: ");

    ndc = atoll(validateNumber(13));

    for (int i = 0; i < count; i++) {
        if (medicineArray[i].ndc == ndc) {
            printf("Id of medicine: %d\nName of medicine: %s\nDescription: %s\nTypical Dosage: %s\n\n",
                   medicineArray[i].id, medicineArray[i].name, medicineArray[i].description, medicineArray[i].typicalDosage);
            free(medicineArray);
            return;
        }
    }
    printf("Medicine with NDC %lld not found.\n", ndc);
    // der skal ændres her så den ikke lukker programmet ved fejl.
    free(medicineArray);
}