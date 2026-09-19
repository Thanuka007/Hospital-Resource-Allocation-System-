#include <stdio.h>

#define Specialty_Count 4
#define MAX_Patients 100
#define Wards_Count 4
#define MAX_Beds 20

extern char patientName [MAX_Patients][50];
extern int patientAge [MAX_Patients];
extern int patientmergencyLevel[MAX_Patients];
extern int patientSpecialtyID [MAX_Patients];
extern int patientWardID [MAX_Patients];
extern int patientDaysAdmitted [MAX_Patients];
extern int patientestimatedWaitingTime [MAX_Patients];
extern double patientEmergencySurcharge [MAX_Patients];
extern double patienttotalWardStayCost [MAX_Patients];
extern double patientGrossTotalBill [MAX_Patients];
extern double patientAgeSubsidyDiscount [MAX_Patients];
extern double patientFinalAmountPayable [MAX_Patients];
extern int patientCount;
extern int specialtyQueueCount[Specialty_Count];
extern const int dailyPatientCap [Specialty_Count];
extern const int consultationTimePerPatient [Specialty_Count];
extern int patientID[MAX_Patients];
extern double patientBaseConsultationFee[MAX_Patients];
extern const double baseConsultationFee [Specialty_Count];
extern const double dailyBedRatePerLKRDay [Wards_Count];
extern const int wardID [Wards_Count];
extern int bedOccupancy [4][20];
extern const int totalBedCapacity [Wards_Count];
extern const char WardsName [Wards_Count][50];
extern int patientAssignedBed[MAX_Patients];

void listSpecialties();
void displayPatientBill(int patientIndex);
void clearscreen();
void savePatientRecord(int patientIndex);



int avilabelBed (int wardIndex){
    int i;
    for (i =0;i< totalBedCapacity[wardIndex];++i){
        if (bedOccupancy[wardIndex][i]==0){
            bedOccupancy[wardIndex][i]=1;
            return i;
        }
    }
    return -1;
}

void patientRegistration (){
    int choice,specialtyIndex,wardIndex;
    if (patientCount >= MAX_Patients) {
        printf("Patient storage is full.\n");
        return;
    }
    printf("Enter patient name                       :");
    scanf(" %49[^\n]",patientName [patientCount]);
    do {
        printf("Enter patient age                        :");
        if (scanf("%d", &patientAge[patientCount]) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            patientAge[patientCount] = -1;
        }
    } while (patientAge[patientCount] < 0 ||
         patientAge[patientCount] > 130);

    do {
        printf("Enter Emergency / Triage Level ""(1 = Normal, 2 = Urgent, 3 = Critical): ");

        if (scanf("%d", &patientmergencyLevel[patientCount]) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            patientmergencyLevel[patientCount] = 0;
        }
    }while (patientmergencyLevel[patientCount] < 1 ||patientmergencyLevel[patientCount] > 3);
    printf("========================================================================\n");
    listSpecialties();
        do {
            printf("Enter Specialty ID (1 to 4)              : ");

            if (scanf("%d", &patientSpecialtyID[patientCount]) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n');
                patientSpecialtyID[patientCount] = 0;
                continue;
            }
            specialtyIndex = patientSpecialtyID[patientCount] - 1;
            if (specialtyIndex >= 0 &&
                specialtyIndex < Specialty_Count &&specialtyQueueCount[specialtyIndex] >= dailyPatientCap[specialtyIndex]) {
                printf("This specialty has reached its daily patient cap.\n");
                patientSpecialtyID[patientCount] = 0;
            }
        } while (patientSpecialtyID[patientCount] < 1 ||patientSpecialtyID[patientCount] > Specialty_Count);

    do {
        printf("Is admitted to ward? (1 = Yes, 0 = No)   : ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Enter 1 or 0.\n");
            while (getchar() != '\n');
            choice = -1;
        }
    } while (choice != 0 && choice != 1);

    if (choice==1){
        do {
            printf("Input Ward ID (1 to 4)                   : ");

            if (scanf("%d", &patientWardID[patientCount]) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n');
                patientWardID[patientCount] = 0;
            }
        } while (patientWardID[patientCount] < 1 ||patientWardID[patientCount] > Wards_Count);

        do {
            printf("Days admitted                            : ");

            if (scanf("%d", &patientDaysAdmitted[patientCount]) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n');
                patientDaysAdmitted[patientCount] = 0;
            }
        } while (patientDaysAdmitted[patientCount] < 1);

        wardIndex = patientWardID[patientCount]-1;
        int bedIndex = avilabelBed(wardIndex);
        if (bedIndex == -1){
            printf("No bed is available in %s. Patient is recorded as OPD.\n", WardsName[wardIndex]);
            patientWardID[patientCount] = 0;
            patientAssignedBed[patientCount] = 0;
            patientDaysAdmitted[patientCount] = 0;
            choice = 0;
        }
        else {
            patientAssignedBed[patientCount]=bedIndex +1;
        }

    }else {
        patientDaysAdmitted [patientCount]=0;
    }

    specialtyIndex = patientSpecialtyID[patientCount] - 1;
    /* Waiting time is calculated BEFORE this patient is added to the queue. */
    patientestimatedWaitingTime[patientCount] = specialtyQueueCount[specialtyIndex] *consultationTimePerPatient[specialtyIndex];
    specialtyQueueCount[specialtyIndex]++;

    patientID[patientCount] = 1001 + patientCount;
    patientBaseConsultationFee[patientCount] = baseConsultationFee[specialtyIndex];

    if (patientmergencyLevel[patientCount] == 1) {
        patientEmergencySurcharge[patientCount] = 0.0;
    }
    else if (patientmergencyLevel[patientCount] == 2) {
            patientEmergencySurcharge[patientCount] =patientBaseConsultationFee[patientCount] * 0.20;
    }
    else {
        patientEmergencySurcharge[patientCount] =patientBaseConsultationFee[patientCount] * 0.50;
}
    if (choice==1){
        wardIndex = patientWardID[patientCount] - 1;
        patienttotalWardStayCost [patientCount]= patientDaysAdmitted[patientCount]*dailyBedRatePerLKRDay [wardIndex];
    }else {
       patienttotalWardStayCost[patientCount] = 0.0 ;
    }




    patientGrossTotalBill [patientCount] = patientBaseConsultationFee[patientCount]+patientEmergencySurcharge [patientCount]+patienttotalWardStayCost [patientCount];

    if (patientAge [patientCount]<5 || patientAge [patientCount]>65){
        patientAgeSubsidyDiscount [patientCount] = patientGrossTotalBill [patientCount]*0.15;
    }
    else {
        patientAgeSubsidyDiscount [patientCount] =0;
    }

    patientFinalAmountPayable [patientCount] = patientGrossTotalBill [patientCount]-patientAgeSubsidyDiscount [patientCount];
    savePatientRecord(patientCount);

    clearscreen();
    displayPatientBill(patientCount);

    patientCount++;

}
