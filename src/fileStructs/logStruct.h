#ifndef P1MEDICINEPROJECT_LOGSTRUCT_H
#define P1MEDICINEPROJECT_LOGSTRUCT_H

#define MAX_DESCRIPTION 256
#define MAX_DATE 20

typedef struct {
    int id;
    char description[MAX_DESCRIPTION];
    int userID;
    char date[MAX_DESCRIPTION];
} LogEntry;

#endif //P1MEDICINEPROJECT_LOGSTRUCT_H
