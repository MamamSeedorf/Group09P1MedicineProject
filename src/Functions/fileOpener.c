#include "../store.h"
#include "ctype.h"

FILE* openMedicineFileRead(){
    FILE* file = fopen("../Databases/medicine.txt", "r");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* openLogFileRead(){
    FILE* file = fopen("../Databases/log.txt", "r");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* openDoctorFileRead(){
    FILE* file = fopen("../Databases/doctor.txt", "r");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}
FILE* openNurseFileRead(){
    FILE* file = fopen("../Databases/nurse.txt", "r");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* openPatientsFileRead(){
    FILE* file = fopen("../Databases/patients.txt", "r");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* openMedicineFileAppend(){
    FILE* file = fopen("../Databases/medicine.txt", "a");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* openLogFileAppend(){
    FILE* file = fopen("../Databases/log.txt", "a");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* openDoctorFileAppend(){
    FILE* file = fopen("../Databases/doctor.txt", "a");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}
FILE* openNurseFileAppend(){
    FILE* file = fopen("../Databases/nurse.txt", "a");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* openPatientsFileAppend(){
    FILE* file = fopen("../Databases/patients.txt", "a");
    if (file == NULL) {
        perror("THE FILE DID NOT OPEN");
        exit(EXIT_FAILURE);
    }
    return file;
}