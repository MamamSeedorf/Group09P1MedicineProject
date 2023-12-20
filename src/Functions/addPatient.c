#include "../store.h"
#include "ctype.h"

void startAddPatientFunction(FILE* patientFile, Patient *addPatient);
int digitsOnly(const char *str);
int lettersOnly(const char *str);
void addPatientHub();
int addAllergies(FILE* patientFile, Patient *addPatient);
void printValueAndSave(FILE* patientFile, Patient *addPatient);

void addPatientHub(){
    FILE *patientFile = openPatientsFileAppend();
    Patient *addPatient = (Patient*)malloc(sizeof(Patient));
    // Run main function
    startAddPatientFunction(patientFile,  addPatient);

    memset(addPatient, 0, sizeof(Patient));
    free(addPatient);
    fclose(patientFile);
}

void startAddPatientFunction(FILE* patientFile, Patient *addPatient){
    char* userAnswerNDC = malloc(sizeof(long long int) + 2);
    int count = 0;

    //Ask for userInput
    printf("Enter social security number: ");
    char* userAnswer = validateNumber(10);

    // Convert the string to a long long int
    char* endptr;
    addPatient->ssn = strtoll(userAnswer, &endptr, 10);

    printf("Enter patients first and last name: ");
    fgets(addPatient->name, sizeof(addPatient->name), stdin);

    // Remove newline character if present
    addPatient->name[strcspn(addPatient->name, "\n")] = '\0';


    printf("Does the patient have any prescriptions? Enter 'yes' or 'no': ");
    char* userAnswer2 = validateYesNo();

    if (strcmp(userAnswer2, "yes") == 0) {
        printf("Enter the NDC for the patients prescriptions, when finished enter 'done': ");
        while (count < MAX_PRESCRIPTIONS) {
            userAnswerNDC = validatePrescription(13);
            if (strcmp(userAnswerNDC, "done") == 0) {
                LogEntry userLOG;
                strncpy(userLOG.description,"User added prescription",MAX_NAME);
                logFunction(userLOG);
                break;
            }
            addPatient->prescriptions[count] = atoll(userAnswerNDC);
            count++;
            printf("Enter NDC (type 'done' to finish): ");
        }

        addPatient->numberofprescriptions = count;
        int interactionRisk = checkInteractionRisks(addPatient->prescriptions, addPatient->numberofprescriptions);
        if(interactionRisk){
            printf("Do you want to proceed despite the interaction risks?\n");
            printf("Enter 'yes' or 'no': ");
            char* interactionRiskAnswer = validateYesNo();

            if(strcmp(interactionRiskAnswer, "yes") == 0){
                printf("\nYou have chosen to proceed\n");
            } else{
                printf("You have chosen to abort\n");
                return;
            }

        }
        printf("Does the patient have any allergies? Enter 'yes' or 'no': ");
        addPatient->numberofallergies = 0;
        char* userAnswer = validateYesNo();
        int result = 1;
        if (strcmp(userAnswer, "yes") == 0) {
            result = addAllergies(patientFile, addPatient);
        }if (result){
            printValueAndSave(patientFile, addPatient);
        }
    }
    else{
        addPatient->numberofallergies = 0;

        int result = 1;
        printf("Does the patient have any allergies? Enter yes or no: ");
        char* userAnswer = validateYesNo();

        if (strcmp(userAnswer, "yes") == 0) {
            result = addAllergies(patientFile, addPatient);
        }
        if (result){
            printValueAndSave(patientFile, addPatient);
        }
    }
}
int addAllergies(FILE* patientFile, Patient *addPatient){
    int countA = 0;
    char* userAnswer;
    //Asking for ndc of the drugs the patient is allergic to, until the user types done.
    printf("Enter NDC of cave (patient allergies), when done enter 'done': ");
    // Loops until userAnswer is "done" or, MAX_ALLERGIES is reached, or input lenght exceeds 13 characters
    while (countA < MAX_ALLERGIES) {
        userAnswer = validatePrescription(13);
        if (strcmp(userAnswer, "done") == 0) {
            break;
        }
        addPatient->allergies[countA] = atoll(userAnswer);
        countA++;
        printf("Enter NDC (when finished enter 'done'): ");
    }
    addPatient->numberofallergies = countA;
    int interactionRisk = checkAllergyPrescritionRisks(addPatient->prescriptions, addPatient->numberofprescriptions, addPatient->allergies, addPatient->numberofallergies);
    if(interactionRisk){
        printf("Do you want to proceed despite the allergy reaction risks\n");
        printf("Enter 'yes' or 'no': ");
        char* interactionRiskAnswer = validateYesNo();
        if(strcmp(interactionRiskAnswer, "yes") == 0){
            printf("\nYou have chosen to proceed\n");
        } else{
            printf("You have chosen to abort\n");
            return 0;
        }
    }
    return 1;
}


void printValueAndSave(FILE* patientFile, Patient *addPatient){

    long long int arraySize1 = addPatient->numberofprescriptions;
    long long int arraySize2 = addPatient->numberofallergies;

    printf("Do you want to add the following patient? Enter yes or no\n");
    printf("Social security number: %lld\nName: %s\n", addPatient->ssn, addPatient->name);
    printf("Prescriptions: ");
    if(arraySize1 > 0){
        printf("[");
        for (int i = 0; i < addPatient->numberofprescriptions; ++i) {
            if(addPatient->prescriptions[i] == 0){
                break;
            }
            if(i != 0){
                printf(";");
            }
            printf("%lld", addPatient->prescriptions[i]);
        }
        printf("]\n");
    }else{
        printf("[]\n");
    }
    printf("Allergies: ");
    if(arraySize2 > 0){
        printf("[");
        for (int i = 0; i < addPatient->numberofallergies; ++i) {
            if(addPatient->allergies[i] == 0){
                break;
            }
            if(i != 0){
                printf(";");
            }
            printf("%lld", addPatient->allergies[i]);

        }

        printf("]\n");
    }else{
        printf("[]\n");
    }
    //Check with the user if it is correct
    printf("Is the patient information correct? enter 'yes' or 'no': ");
    char* userAnswer = validateYesNo();
        if(strcmp(userAnswer, "yes") == 0){
            // Writing patient information to the patientFile in the ordered format
            fprintf(patientFile, "%d,%lld,%s,", findNextId(openPatientsFileRead()), addPatient->ssn, addPatient->name);
            LogEntry userLOG;
            strncpy(userLOG.description,"User added new patient to file",MAX_NAME);
            logFunction(userLOG);

            // Writes prescription information to the patientFile
            if(arraySize1 > 0){
                fprintf(patientFile, "[");
                for (int i = 0; i < addPatient->numberofprescriptions; ++i) {
                    if(addPatient->prescriptions[i] == 0){
                        break;
                    }
                    if(i != 0){
                        fprintf(patientFile,";");
                    }
                    fprintf(patientFile,"%lld", addPatient->prescriptions[i]);
                }
                fprintf(patientFile, "],");
            }else{
                fprintf(patientFile, "[],");
            }

            // Writes allergies information to the patient file
            if(arraySize2 > 0){
                fprintf(patientFile,"[");
                for (int i = 0; i < addPatient->numberofallergies; ++i) {
                    if(addPatient->allergies[i] == 0){
                        break;
                    }
                    if(i !=0){
                        fprintf(patientFile, ";");
                    }
                    fprintf(patientFile, "%lld", addPatient->allergies[i]);
                }
                fprintf(patientFile,"]\n");
            }else{
                fprintf(patientFile, "[]\n");
            }
            printf("The data have now been added!\n");
        }else{
            addPatientHub();
        }
}

// This function makes sure only numbers are valid
int digitsOnly(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            // If all characters are digits
            // if not all characters are digits
            return 0;
        }
    }
    return 1;  // if not all characters are digits
}
// This function makes sure only letters are valid
int lettersOnly(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isalpha((unsigned char)str[i])) {
            return 0;  // Non-letter character found
        }
    }
    return 1;  // Only letters in the string
}
