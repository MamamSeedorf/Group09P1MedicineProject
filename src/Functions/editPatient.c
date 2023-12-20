#include "../store.h"


void rewritePatientFile(Patient *patientArray, int count){
    FILE *tempFile = fopen("../Databases/temptemp.txt", "w");
    if (!tempFile) {
        printf("Unable to create a temporary file");
        return;
    }
    for (int i = 0; i < count; ++i) {
        fprintf(tempFile, "%d,%lld,%s,[",patientArray[i].id, patientArray[i].ssn, patientArray[i].name);

        // Writes prescription information to the patientFile
        for (int j = 0; j < patientArray[i].numberofprescriptions; ++j) {
            if (j != 0){
                fprintf(tempFile, ";");
            }
            fprintf(tempFile, "%lld", patientArray[i].prescriptions[j]);
        }

        fprintf(tempFile, "],["); // Indicates end of prescriptions and start of allergies

        // Writes allergies information to the patient file
        for (int j = 0; j < patientArray[i].numberofallergies; ++j) {
            if (j != 0){
                fprintf(tempFile, ";");
            }
            fprintf(tempFile, "%lld", patientArray[i].allergies[j]);

        }
        fprintf(tempFile, "]\n");
    }

    fclose(tempFile);
    remove("../Databases/patients.txt");
    rename("../Databases/temptemp.txt", "../Databases/patients.txt");

}

Patient allergyAdder(Patient newPatient){
    int countA = 0;
    char* userAnswer;
    memset(newPatient.allergies, 0, sizeof(newPatient.allergies));
    //Asking for ndc of the drugs the patient is allergic to, until the user types done.
    printf("Enter NDC of cave (patient allergies), when done enter 'done': ");

    // Loops until userAnswer is "done" or, MAX_ALLERGIES is reached, or input lenght exceeds 13 characters
    while (countA < MAX_ALLERGIES) {
        userAnswer = validatePrescription(13);
        LogEntry userLOG;
        strncpy(userLOG.description,"User edited patient file",MAX_NAME);
        logFunction(userLOG);

        if (strcmp(userAnswer, "done") != 0) {
            newPatient.allergies[countA] = atoll(userAnswer);
            countA++;
        } else {
            break;
        }
        printf("Enter NDC (when finished enter 'done'): ");
    }
    newPatient.numberofallergies = countA;

    int interactionRisk = checkAllergyPrescritionRisks(newPatient.prescriptions, newPatient.numberofprescriptions, newPatient.allergies, newPatient.numberofallergies);
    if(interactionRisk){
        printf("Do you want to proceed despite the allergy reaction risks\n");
        printf("Enter 'yes' or 'no': ");
        char* interactionRiskAnswer = validateYesNo();
        if(strcmp(interactionRiskAnswer, "yes") == 0){
            printf("\nYou have chosen to proceed\n");
        } else{
            printf("You have chosen to abort\n");
            newPatient.id = -1;
            return newPatient;
        }
    }

    return newPatient;
}

Patient prescriptionAdder(Patient newPatient){
    printf("Enter the NDC for the patients prescriptions(When finished enter 'done'): ");
    char* userAnswerNDC;
    int count = 0;
    memset(newPatient.prescriptions, 0, sizeof(newPatient.prescriptions));
    while (count < MAX_PRESCRIPTIONS) {
        userAnswerNDC = validatePrescription(13);
        if (strcmp(userAnswerNDC, "done") == 0) {
            break;
        }
        newPatient.prescriptions[count] = atoll(userAnswerNDC);
        count++;
        printf("Enter NDC (type 'done' to finish): ");
    }
    newPatient.numberofprescriptions = count;
    int interactionRisk = checkInteractionRisks(newPatient.prescriptions, newPatient.numberofprescriptions);
    if(interactionRisk){
        printf("Do you want to proceed despite the interaction risks?\n");
        printf("Enter 'yes' or 'no': ");
        char* interactionRiskAnswer = validateYesNo();

        if(strcmp(interactionRiskAnswer, "yes") == 0){
            printf("\nYou have chosen to proceed\n");
        } else{
            printf("You have chosen to abort\n");
            newPatient.id = -1;
            return newPatient;
        }
    }
    return newPatient;
}

void editPatient(){
    Patient foundPatient = PatientInformation();
    if(foundPatient.id == -1){
        return;
    }
    int editChoice = 0;
    printf("Choose the data you want to edit:\n");
    printf("(1) SSN\n");
    printf("(2) Name\n");
    printf("(3) Prescriptions:\n");
    printf("(4) Allergies:\n");
    scanf("%d", &editChoice);
    getchar();
    char* userAnswer;
    char binaryAnswer;
    long long int ssn = 0;
    int validInput = 0;
    switch(editChoice) {
        case 1:
            printf("Enter the new SSN of the patient: ");
            userAnswer = validateNumber(10);
            ssn = atoll(userAnswer);
            printf("Are you sure you want to change the patients SSN to %s enter 'yes' or 'no': ", userAnswer);
            char* userAnswer = validateYesNo();
            if (strcmp(userAnswer, "yes") == 0){
                foundPatient.ssn = ssn;
            }else{
                printf("Aborting edit of patient...\n");
            }
            break;
        case 2:
            printf("Enter the new name of the patient: ");
            fgets(userAnswer, sizeof(userAnswer), stdin);

            if (strchr(userAnswer, '\n')) {
                userAnswer[strcspn(userAnswer, "\n")] = 0;
            }
            printf("Are you sure you want to change the patients name to %s enter 'yes' or 'no': ", userAnswer);
            userAnswer = validateYesNo();
            if (strcmp(userAnswer, "yes") == 0){
                strncpy(foundPatient.name, userAnswer, MAX_ANSWER_LEN);
            }else{
                printf("Aborting edit of patient...\n");
            }
            break;
        case 3:
            foundPatient = prescriptionAdder(foundPatient);
            break;
        case 4:
            foundPatient = allergyAdder(foundPatient);
            break;
        default:
            printf("Invalid input\n");
            return;
    }
    if (foundPatient.id == -1){
        return;
    }
    // INSERT THE EDITED PATIENT ON THEIR PLACE IN FILE:

    FILE *readFile = fopen("../Databases/patients.txt", "r");
    if (readFile == NULL) {
        perror("THE FILE DID NOT OPEN");
        EXIT_FAILURE;
    }
    char line[MAX_LINE_LENGTH];
    Patient *allPatients = (Patient *)malloc(MAX_PATIENT_NAME * sizeof(Patient));
    int count = populatePatientArray(readFile, allPatients);
    for (int i = 0; i < count; ++i) {
        if(allPatients[i].id == foundPatient.id){
            allPatients[i] = foundPatient;
        }
    }
    fclose(readFile);
    rewritePatientFile(allPatients, count);
    printf("The patient has been edited\n");

}