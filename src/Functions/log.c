#include "../store.h"




void logFunction(LogEntry user){


    //Finds current date
    time_t currentTime;
    time(&currentTime);
    FILE *fp = openLogFileAppend();
    int Id = findNextId(openLogFileRead());
    fclose(fp);
    FILE *fp1=fopen("../Databases/log.txt","a");
    strcpy(user.date, ctime(&currentTime));
    if(fp==NULL)
        printf("File unable to open");
    fprintf(fp1,"%d,\"%s\",%d,%s",Id,user.description,user.userID,user.date);
    fclose(fp1);
}