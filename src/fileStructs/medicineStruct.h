#define MAX_NAME 100
#define MAX_DESCRIPTION 256
#define MAX_DOSAGE_LENGTH 100
#define MAX_INTERACTION_RISKS 10

typedef struct {
    int id;
    long long int ndc;
    char name[MAX_NAME];
    char description[MAX_DESCRIPTION];
    long long int numberOfInteractionRisks;
    long long int interactionRisks[MAX_INTERACTION_RISKS];
    char typicalDosage[MAX_DOSAGE_LENGTH];
} Medicine;
