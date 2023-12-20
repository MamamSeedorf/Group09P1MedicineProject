#include "../store.h"

#ifndef P1MEDICINEPROJECT_DIPENSER_H
#define P1MEDICINEPROJECT_DIPENSER_H

Patient PatientInformation() {
    Patient foundPatient;
    FILE *file = openPatientsFileRead();

    char line[MAX_LINE_LENGTH];
    Patient *patientArray = (Patient *)malloc(MAX_PATIENT_NAME * sizeof(Patient));
    int count = populatePatientArray(file, patientArray);

    fclose(file);

    long long int ssn;
    printf("Enter the social security number of the patient: ");

    ssn = atoll(validateNumber(10));

    for (int i = 0; i < count; i++) {
        if (patientArray[i].ssn == ssn) {
            printf("Social security number of patient: %lld\nName of patient: %s\n", patientArray[i].ssn, patientArray[i].name);

            // Print Prescriptions
            printf("Prescriptions:\n");
            for (int j = 0; j < patientArray[i].numberofprescriptions; j++) {
                printf("%lld\n", patientArray[i].prescriptions[j]);
            }

            // Print Allergies
            printf("Allergies:\n");
            for (int k = 0; k < patientArray[i].numberofallergies; k++) {
                printf("%lld\n", patientArray[i].allergies[k]);
            }
            foundPatient = patientArray[i];
            free(patientArray);
            return foundPatient;
        }
    }
    printf("Patient social security number %lld not found.\n", ssn);
    // der skal ændres her så den ikke lukker programmet ved fejl.
    free(patientArray);
    // returning a patient with id=-1 (impossible) to indicate no valid patient was found
    foundPatient.id = -1;
    return foundPatient;
}

#endif //P1MEDICINEPROJECT_DIPENSER_H