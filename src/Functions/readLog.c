#include "../store.h"

void readLog(){
    FILE *file = openLogFileRead();
    LogEntry* logArray = (LogEntry *)malloc(MAX_MEDCINES * sizeof(LogEntry));
    int count = populateLogArray(file, logArray);
    fclose(file);
    for (int i = 0; i < count; ++i) {
        printf("ID of Log: %d\nDescription of log: %s. User ID: %d, date: %s\n",logArray[i].id,logArray[i].description,logArray[i].userID,logArray[i].date);
    }
}