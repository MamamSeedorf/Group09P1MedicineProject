#include "../store.h"

#ifndef P1MEDICINEPROJECT_DIPENSER_H
#define P1MEDICINEPROJECT_DIPENSER_H
void dispenseMedicine();
void dispenseMedicine() {
    //Open patients.txt
    printf("You have chosen to dispense medicine to a patient.\n");
    FILE *patientsFile = openPatientsFileRead();
    FILE *medicineFile = openMedicineFileRead();

    // Define useranswer and request user to put in the name of the patient they want to dispense medicine to.
    char* userAnswer;

    printf("Enter the ssn of the patient, which you would like to dispense medicine to: \n");
    userAnswer = validateNumber(10);
    long long int userAnswerlld = atoll(userAnswer);
    Patient *patientArray = (Patient *) malloc(MAX_PATIENT_NAME * sizeof(Patient));
    int count = populatePatientArray(patientsFile, patientArray);
    // Loop that compares each name in patients.txt to the useranswer, continues if the name is found.
    for (int i = 0; i < count; ++i) {
        if (userAnswerlld == patientArray[i].ssn) {
            printf("You have chosen %s with the ID %d and ssn %lld. Their prescribed medicines are \n", patientArray[i].name, patientArray[i].id, patientArray[i].ssn);
            // Loop that checks each prescribed medicine and prints them.
            for (int j = 0; j < patientArray[i].numberofprescriptions; ++j) {
                printf("%lld \n", patientArray[i].prescriptions[j]);
            }
            if(patientArray[i].numberofprescriptions==0){
                printf("The patient does not have any prescribed medicines.");
                break;
            }

            // Define new user input and ask user to choose the NDC of the medicine.
            char* userAnswer2;

            printf("Choose the NDC of a medicine from the list of prescriptions to dispense for the patient:");
            userAnswer2 = validateNumber(13);
            long long int userAnswerlld2 = atoll(userAnswer2);

            int isPrescription = 0;

            // Loop that checks if useranswer is a prescribed medicine. If yes, lets them dispense it.
            for (int k = 0; k < patientArray[i].numberofprescriptions; ++k) {
                if(userAnswerlld2 == patientArray[i].prescriptions[k]) {
                    isPrescription = 1;

                    // Open medicine.txt file and allocate storage.
                    char line2[MAX_NAME];
                    Medicine *medcineArray = (Medicine *) malloc(MAX_NAME * sizeof(Medicine));
                    int count2 = populateMedicineArray(medicineFile, medcineArray);
                    // Find the name of the medicine being dispensed and print it after confirming your choice!
                    for (int j = 0; j < count2; ++j) {
                        if (userAnswerlld2==medcineArray[j].ndc) {
                            printf("Are you sure you want to dispense %s to %s \nEnter yes or no:",medcineArray[j].name,patientArray[i].name);
                            char* userAnswer3 = validateYesNo();


                            free(patientArray);
                            fclose(patientsFile);
                            free(medcineArray);
                            fclose(medicineFile);

                            if(strcmp(userAnswer3,"yes") == 0){
                                printf("You have successfully dispensed %s to %s\n",medcineArray[j].name,patientArray[i].name);
                                LogEntry userLOG;
                                strncpy(userLOG.description,"User dispensed medicine file",MAX_NAME);
                                logFunction(userLOG);
                                break;
                            }
                            else if (strcmp(userAnswer3,"no") == 0) {
                                printf("Lucky you, good choice!\n");
                                break;
                            }
                        }
                        if(j==count2-1) {
                            printf("The medicine is not in the database.\n");
                        }

                    }
                }
            }
            if (!isPrescription) {
                printf("The medicine is not a prescribed medicine for %s.\n",patientArray[i].name);
            }
        }
    }
}



#endif //P1MEDICINEPROJECT_DIPENSER_H