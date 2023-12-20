#ifndef P1MEDICINEPROJECT_PATIENTSTRUCT_H
#define P1MEDICINEPROJECT_PATIENTSTRUCT_H

#define MAX_PATIENT_NAME 100
#define MAX_PRESCRIPTIONS 50
#define MAX_ALLERGIES 50

typedef struct {
    int id;
    long long int ssn;
    char name[MAX_PATIENT_NAME];
    long long int prescriptions[MAX_PRESCRIPTIONS];
    int numberofprescriptions;
    long long int allergies[MAX_ALLERGIES];
    int numberofallergies;
} Patient;
#endif //P1MEDICINEPROJECT_PATIENTSTRUCT_H
