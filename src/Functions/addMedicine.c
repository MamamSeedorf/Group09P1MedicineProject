#include "../store.h"

void startAddMedicineFunction(FILE* medicineFile, Medicine *addMedicine);

int digitsOnly_two(const char *str);
int lettersOnly_two(const char *str);
void typicalDosage(Medicine *addMedicine);

void addMedicineHub(){
    FILE *medicineFile = openMedicineFileAppend();
    Medicine *addMedicine = (Medicine*)malloc(sizeof(Medicine));

    //Run function
    startAddMedicineFunction(medicineFile, addMedicine);
    //free memory
    memset(addMedicine, 0, sizeof(Medicine));
    free(addMedicine);

    //close file
    fclose(medicineFile);

}

void startAddMedicineFunction(FILE* medicineFile, Medicine *addMedicine){
    char* userAnswer;
    int count = 0;


    printf("You chosen to add new medicine to the database\n");

    printf("Enter the drugs NDC:");
    userAnswer = validateNumber(13);
    //Converting useranswer to addmedicine-> (string to long long int)
    char* endptr;
    addMedicine->ndc = strtoll(userAnswer, &endptr, 10);

    printf("Enter medicine name:");
    fgets(addMedicine->name, sizeof(addMedicine->name), stdin);
    addMedicine->name[strcspn(addMedicine->name, "\n")] = '\0';

    printf("Enter a short description of the drug:");
    fgets(addMedicine->description, sizeof(addMedicine->description), stdin);
    addMedicine->description[strcspn(addMedicine->description, "\n")] = '\0';

    printf("Does this drug have any interaction risks?\n");
    printf("Enter yes or no:");
    char* userAnswer2 = validateYesNo();
    // If user types yes it uses the function interactionRiskFunction, and if no, uses noInteractionRisksFunction
    if (strcmp(userAnswer2, "yes") == 0) {
        printf("Enter the drugs NDC. When done, enter 'done': ");
        while (count < MAX_INTERACTION_RISKS) {
            userAnswer = validatePrescription(13);
            if (strcmp(userAnswer, "done") == 0) {
                break;
            }
            addMedicine->interactionRisks[count] = atoll(userAnswer);
            count++;
            printf("Enter the drugs NDC. When done, enter 'done': ");
        }
        addMedicine->numberOfInteractionRisks = count;
    }


    typicalDosage(addMedicine);


    int arraySize = addMedicine->numberOfInteractionRisks;

    printf("\nYou want to add the following medicine:\n");
    printf("NDC:%lld\nName: %s\nDescription: %s\n", addMedicine->ndc, addMedicine->name, addMedicine->description);
    printf("Interaction risks: ");
    if (arraySize > 0) {
        printf("[");
        for (int i = 0; i < count; i++) {
            if (addMedicine->interactionRisks[i] == 0) {
                break;  // Stop printing when encountering a zero
            }

            if (i != 0) {
                printf(";");
            }

            printf("%lld", addMedicine->interactionRisks[i]);

        }
        printf("]\n");

    }else{
        printf("[]\n");
    }


    printf("Typical Dosage: %s\n", addMedicine->typicalDosage);

    printf("Is this correct?\nEnter yes or no: ");
    char* userAnswer3 = validateYesNo();


    if(strcmp(userAnswer3, "yes") == 0){
        printf("The data will now be added to the Database!\n");
        fprintf(medicineFile, "%d,%lld,%s,\"%s\",[", findNextId(openMedicineFileRead()), addMedicine->ndc, addMedicine->name, addMedicine->description);

        if (arraySize > 0) {
            for (int i = 0; i < addMedicine->numberOfInteractionRisks; i++) {
                if (addMedicine->interactionRisks[i] == 0) {
                    break;
                }
                if (i != 0){
                    fprintf(medicineFile, ";");

                }
                fprintf(medicineFile, "%lld", addMedicine->interactionRisks[i]);
            }
        }

        fprintf(medicineFile, "],\"%s\"\n", addMedicine->typicalDosage);
    } else {
        addMedicineHub();
    }
}

void typicalDosage(Medicine *addMedicine){
    printf("Enter Typical Dosage: ");
    getchar();
    fgets(addMedicine->typicalDosage, sizeof(addMedicine->typicalDosage), stdin);
    addMedicine->typicalDosage[strcspn(addMedicine->typicalDosage, "\n")] = '\0';

}


// This function makes sure only numbers are valid
int digitsOnly_two(const char *str) {
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
int lettersOnly_two(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isalpha((unsigned char)str[i])) {
            return 0;  // Non-letter character found
        }
    }
    return 1;  // Only letters in the string
}

int checkInteractionRisks(long long int *medicineList, int lengthOfMedicineList) {
    printf("\nChecking for interaction risks...\n\n");
    FILE *file = openMedicineFileRead();
    Medicine *medicineArray = (Medicine *) malloc(MAX_MEDCINES * sizeof(Medicine));
    long long int **badInteractionPair = allocateInteractionPair();
    int count = populateMedicineArray(file, medicineArray);
    int badInteractionArrayCount = 0;
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < lengthOfMedicineList - 1; ++j) {
            if (medicineArray[i].ndc == medicineList[j]) {
                for (int l = j + 1; l < lengthOfMedicineList; ++l) {
                    for (int k = 0; k < medicineArray[i].numberOfInteractionRisks; ++k) {
                        if (medicineArray[i].interactionRisks[k] == medicineList[l]) {
                            badInteractionPair[badInteractionArrayCount][0] = medicineList[j];
                            badInteractionPair[badInteractionArrayCount][1] = medicineList[l];
                            badInteractionArrayCount++;
                        }
                    }
                }
            }
        }
    }
    if(badInteractionArrayCount == 0){
        printf("There are no interaction risks in the prescription list\n");
        return 0;
    }
    else{
        printf("There has been found medicines with interaction risks:\n");
        for (int i = 0; i < badInteractionArrayCount; ++i) {
            printf("%lld has a interaction risk with %lld\n", badInteractionPair[i][0], badInteractionPair[i][1]);
        }
        return 1;
    }
}
int checkAllergyPrescritionRisks(long long int *medicineList, int lengthOfMedicineList, long long int *allergyList, int lengthOfAllergyList) {
    printf("\nChecking for interaction risks...\n\n");
    long long int *allergyReactions = malloc(MAX_MEDCINES * sizeof(long long int));
    int allergyReactionCount = 0;

    for (int i = 0; i < lengthOfAllergyList; ++i) {
        for (int j = 0; j < lengthOfMedicineList; ++j) {
                if(allergyList[i] == medicineList[j]){
                    allergyReactions[allergyReactionCount] = allergyList[i];
                    allergyReactionCount++;
            }
        }

    }
    if(allergyReactionCount == 0){
        printf("There are no allergy risks in the prescription list\n");
        return 0;
    }
    else{
        printf("There has been found medicines with allergy risks:\n");
        for (int i = 0; i < allergyReactionCount; ++i) {
            printf("The patient has an allergy to the prescribed medicine: %lld\n", allergyReactions[i]);
        }
        return 1;
    }
}