#ifndef P1MEDICINEPROJECT_DOCTORSTRUCT_H
#define P1MEDICINEPROJECT_DOCTORSTRUCT_H

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    int id;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} Doctor;

#endif //P1MEDICINEPROJECT_DOCTORSTRUCT_H
