
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAX_ANSWER_LEN 100
#define MAX_LINE_LENGTH 1000
#define MAX_MEDCINES 100
#define MAX_NAME_PARSER 100


#include "../src/fileStructs/doctorStruct.h"
#include "../src/fileStructs/logStruct.h"
#include "../src/fileStructs/nurseStruct.h"
#include "../src/fileStructs/patientStruct.h"
#include "../src/fileStructs/medicineStruct.h"

int parseLog(char *line,LogEntry *log);
int parsePatient(char *line, Patient *patient);
int parseMedicine(char *line, Medicine *med);
int parseUser(char *line, Nurse *nurse);

void readLog();

void logFunction(LogEntry ID);
//Medicine


void readMedicine();
void NdcInformation();
void startAddMedicineFunction(FILE* medicineFile, Medicine *addMedicine);
int digitsOnly_two(const char *str);
int lettersOnly_two(const char *str);
void typicalDosage(Medicine *addMedicine);
void addMedicineHub();
int checkInteractionRisks(long long int *medicineList, int lengthOfMedicineList);

//Patient header files
int addAllergies(FILE* patientFile, Patient *addPatient);
void readPatient();
Patient PatientInformation();
void startAddPatientFunction(FILE* patientFile, Patient *addPatient);
void rewritePatientFile(Patient *patientArray, int count);
void editPatient();


//AddPatient header files
// This function makes sure only numbers are valid
int digitsOnly(const char *str);
int lettersOnly(const char *str);
void addPatientHub();


// If no prescriptions or allergies this function is used to write "[],[]# in the text file
void noPrescriptionNoAllergy(FILE* patientFile, Patient* addPatient);
void addPrescription(FILE* patientFile, Patient *addPatient);



//User
void runDoctor();
void dispenseMedicine();
void runNurse();

int startLoginFunction();

int findNextId(FILE* file);

FILE* openLogFileRead();
FILE* openPatientsFileRead();
FILE* openNurseFileRead();
FILE* openDoctorFileRead();
FILE* openMedicineFileRead();
FILE* openLogFileAppend();
FILE* openPatientsFileAppend();
FILE* openNurseFileAppend();
FILE* openDoctorFileAppend();
FILE* openMedicineFileAppend();
int populateMedicineArray(FILE* file, Medicine* medicineArray);
int populateLogArray(FILE* file, LogEntry* logArray);
int populatePatientArray(FILE* file, Patient* patientArray);
long long int** allocateInteractionPair();

int parseInt(char **token, char **rest);
long long parseLongLongInt(char **token, char **rest);
void parseString(char **token, char **rest, char *output, int maxLen);
int parseArray(char **token, char **rest, long long int *array);
char* validateYesNo();
char* validateNumber(int length);
char* validatePrescription(int length);
int checkAllergyPrescritionRisks(long long int *medicineList, int lengthOfMedicineList, long long int *allergyList, int lengthOfAllergyList);

