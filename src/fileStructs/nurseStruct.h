#ifndef P1MEDICINEPROJECT_NURSESTRUCT_H
#define P1MEDICINEPROJECT_NURSESTRUCT_H

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    int id;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} Nurse;

#endif //P1MEDICINEPROJECT_NURSESTRUCT_H
