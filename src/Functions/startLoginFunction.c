#include "../store.h"

int startLoginFunction() {
    char userName[MAX_USERNAME];
    char passWord[MAX_PASSWORD];

    // Open user file
    FILE* nurseLogin = openNurseFileRead();

    // Open admin file
    FILE* doctorLogin = openDoctorFileRead();

    Doctor *doctorLogins = (Doctor*)malloc(sizeof(*doctorLogins));
    Nurse *nurseLogins = (Nurse*)malloc(sizeof(*nurseLogins));

    int nurseFound = 0;
    int doctorFound = 0;

    printf("Login\n");
    printf("Enter Username: ");
    fgets(userName, sizeof(userName), stdin);
    userName[strcspn(userName, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(passWord, sizeof(passWord), stdin);
    passWord[strcspn(passWord, "\n")] = '\0';

    // Check doctor file
    while (fscanf(doctorLogin, "%d,%[^,],%[^\n]", &doctorLogins->id, doctorLogins->username, doctorLogins->password) == 3) {
        if (strcmp(userName, doctorLogins->username) == 0 && strcmp(passWord, doctorLogins->password) == 0) {
            printf("Welcome Doctor %s\n", doctorLogins->username);
            doctorFound = 1;
            LogEntry userID;
            userID.userID=doctorLogins->id;
            strncpy(userID.description,"Doctor logged in",MAX_NAME);
            logFunction(userID);
            break;
        }
    }

    // Rest the file pointer to the beginning of the text file.
    fseek(doctorLogin, 0, SEEK_SET);

    // Check nurse file
    while (fscanf(nurseLogin, "%d,%[^,],%[^\n]", &nurseLogins->id, nurseLogins->username, nurseLogins->password) == 3) {

        if (strcmp(userName, nurseLogins->username) == 0 && strcmp(passWord, nurseLogins->password) == 0) {
            printf("Welcome Nurse %s\n", nurseLogins->username);
            LogEntry userID;
            strncpy(userID.description,"Nurse logged in",MAX_NAME);
            userID.userID=nurseLogins->id;
            logFunction(userID);
            nurseFound = 1;
            break;
        }
    }
    fclose(doctorLogin);
    fclose(nurseLogin);
    free(nurseLogins);
    free(doctorLogins);

    if(doctorFound==1) {
        return 1;
    }
    else if (nurseFound==1) {
        return 2;
    }
    else{
        return 3;
    }

}