#include "store.h"


void return_function_doctor() {
    char* choice;
    printf("Do you want to return to options menu?\n");
    printf("Enter 'yes' or 'no': ");
    choice = validateYesNo();
    if(strcmp(choice, "yes")==0) {
        runDoctor();
    }else{
        exit(EXIT_SUCCESS);
    }
}

void return_function_nurse() {
    char* choice;
    printf("Do you want to return to options menu?\n");
    printf("Enter 'yes' or 'no': ");
    choice = validateYesNo();
    if(strcmp(choice, "yes")==0) {
        runNurse();
    }else{
        exit(EXIT_SUCCESS);
    }
}


void runDoctor(){
        int doctorChoice;
        printf("(1) Add Patient\n");
        printf("(2) Add Medicine\n");
        printf("(3) Log\n");
        printf("(4) Display Medicine Database\n");
        printf("(5) Display Patient Database\n");
        printf("(6) Display specific medicine\n");
        printf("(7) Display specific patient\n");
        printf("(8) Edit specific patient\n");
        printf("(9) Dispense medicine\n");
        printf("(10) Logout\n");
        scanf("%d", &doctorChoice);
        getchar();
    switch(doctorChoice) {
        case 1:
            addPatientHub();
            break;
        case 2:
            addMedicineHub();
            break;
        case 3:
            readLog();
            break;
        case 4:
            readMedicine();
            break;
        case 5:
            readPatient();
            break;
        case 6:
            NdcInformation();
            break;
        case 7:
            PatientInformation();
            break;
        case 8:
            editPatient();
            break;
        case 9:
            dispenseMedicine();
            break;
        case 10:
            printf("Logging out...\n");
            break;
        default:
            printf("Unrecognized command\n");
            break;
    }
    return_function_doctor();
}
void runNurse() {
        int nurseChoice;
        printf("Please choose between the following: \n");
        printf("(1) Search for patient\n");
        printf("(2) Search for medicine\n");
        printf("(3) Dispense medicine for patient\n");
        printf("(4) Logout\n");
        scanf("%d", &nurseChoice);
        getchar();
        switch (nurseChoice) {
            case 1:
                PatientInformation();
                break;
            case 2:
                NdcInformation();
                break;
            case 3:
                dispenseMedicine();
                break;
            case 4:
                printf("Logging out...\n");
                break;
            default:
                printf("Unrecognized command");
                break;
        }
        return_function_nurse();
}
int main(void) {
    printf("Starting program...\n\n");
    printf("Welcome!\n");
while(1) {

    int loginResult = startLoginFunction();
        switch (loginResult) {
            case 1:
                runDoctor();
                break;
            case 2:
                runNurse();
                break;
            case 3:
                printf("Login failed\n");
                break;
            default:
                perror("EXIT FAILURE");
                break;
        }
}
}