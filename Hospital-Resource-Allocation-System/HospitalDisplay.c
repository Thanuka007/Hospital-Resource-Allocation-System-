#include <stdio.h>

#define Specialty_Count 4
#define MAX_Patients 100
#define Wards_Count 4
#define MAX_Beds 20

extern const char specialtyNames[Specialty_Count][30];
extern const int specialtyID [Specialty_Count];
extern const double baseConsultationFee [Specialty_Count];
extern const int consultationTimePerPatient [Specialty_Count];
extern const int dailyPatientCap [Specialty_Count];
extern const char WardsName [Wards_Count][50];
extern const int wardID [Wards_Count];
extern const double dailyBedRatePerLKRDay [Wards_Count];
extern const int totalBedCapacity [Wards_Count];
extern int patientID[MAX_Patients];
extern char patientName [MAX_Patients][50];
extern int patientAge[MAX_Patients];
extern int patientSpecialtyID [MAX_Patients];
extern int patientWardID [MAX_Patients];
extern int patientAssignedBed[MAX_Patients];
extern int patientmergencyLevel[MAX_Patients];
extern double patientBaseConsultationFee[MAX_Patients];
extern double patientEmergencySurcharge [MAX_Patients];
extern double patienttotalWardStayCost [MAX_Patients];
extern double patientGrossTotalBill [MAX_Patients];
extern double patientAgeSubsidyDiscount [MAX_Patients];
extern double patientFinalAmountPayable [MAX_Patients];
extern int patientestimatedWaitingTime [MAX_Patients];
extern int patientCount;
extern int bedOccupancy [4][20];

int getOccupiedBedCount(int wardIndex) {
    int i, count = 0;
    for (i = 0; i < totalBedCapacity[wardIndex]; ++i) {
        count += bedOccupancy[wardIndex][i];
    }
    return count;
}

void printMenu (){
    printf("\n============SMART HOSPITAL MAIN MENU============\n");
    printf("01. Register a patient and generate a bill\n");
    printf("02. Display priority order\n");
    printf("03. Display bed occupancy status\n");
    printf("04. Display doctor specialties\n");
    printf("05. Display hospital wards\n");
    printf("06. Generate performance report\n");
    printf("07. Exit\n");
    printf("\n============************************============\n");
    }


void listSpecialties (){
    int i;
    printf("Doctor Specialties Data\n");
    printf("%-12s %-30s %-28s %-25s %-18s\n","Specialty ID","Specialty Name","Base Consultation Fee (LKR)","Consultation Time/Patient","Daily Patient Cap");

    for (i=0;i<Specialty_Count;++i){
        printf("%-12d %-30s %-28.2f %-25d %-18d\n",specialtyID[i],specialtyNames[i],baseConsultationFee[i],consultationTimePerPatient[i],dailyPatientCap[i]);

    }
}

void listWardsData (){
    int i;
    printf("Hospital Wards Data\n");
    printf("%-10s %-30s %-28s %-20s %-18s\n","Ward ID","Ward Name","Daily Bed Rate (LKR / Day)","Total Bed Capacity","Bed Availability");

    for (i=0;i< Wards_Count;++i){
        printf("%-10d %-30s %-28.2f %-20d %-18d\n",wardID[i],WardsName[i],dailyBedRatePerLKRDay[i],totalBedCapacity[i],0);

    }
}

void displayPatientBill(int patientIndex){
    const char urgencyNames[4][10] = {"","Normal","Urgent","Critical"};
    printf("============================================================\n");
    printf("           SMART HOSPITAL ADMISSION & BILL\n");
    printf("------------------------------------------------------------\n");
    printf("Patient ID              : PAT- %d\n",patientID[patientIndex]);
    printf("Patient Name            : %s\n",patientName[patientIndex]);
    printf("Age                     : %d Years%s\n",patientAge[patientIndex],(patientAge[patientIndex] < 5 || patientAge[patientIndex] > 65) ? " (15% Subsidy Eligible)" : "");
    printf("Specialty               : %s\n",specialtyNames[patientSpecialtyID[patientIndex]-1]);
    if (patientWardID[patientIndex] == 0) {
        printf("Assigned Ward           : Not Admitted  \n");
    } else {
        printf("Assigned Ward           : %s (Bed #%d)\n",WardsName[patientWardID[patientIndex] - 1], patientAssignedBed[patientIndex]);
    }
    printf("Urgency Level           : Level %d (%s)\n", patientmergencyLevel[patientIndex],urgencyNames[patientmergencyLevel[patientIndex]]);
    printf("------------------------------------------------------------\n");
    printf("Base Consultation Fee   : LKR %.2f\n",patientBaseConsultationFee[patientIndex]);
    printf("Emergency Surcharge     : LKR %.2f\n",patientEmergencySurcharge[patientIndex]);
    printf("Ward Stay Cost          : LKR %.2f\n",patienttotalWardStayCost[patientIndex]);
    printf("------------------------------------------------------------\n");
    printf("Gross Total Bill        : LKR %.2f\n",patientGrossTotalBill[patientIndex]);
    printf("Age Subsidy Discount    : LKR %.2f\n",patientAgeSubsidyDiscount[patientIndex]);
    printf("------------------------------------------------------------\n");
    printf("Final Payable Amount    : LKR %.2f\n",patientFinalAmountPayable[patientIndex]);
    printf("Estimated Waiting Time  : %d mins\n", patientestimatedWaitingTime[patientIndex]);
    printf("============================================================\n");
}


void displayPriorityOrder() {
    int order[MAX_Patients];
    int i, j, temporary, patientIndex;
    const char urgencyNames[4][10] = {"", "Normal", "Urgent", "Critical"};

    if (patientCount == 0) {
        printf("\nNo patients have been registered yet.\n");
        return;
    }
    for (i = 0; i < patientCount; ++i) order[i] = i;

    for (i = 0; i < patientCount - 1; ++i) {
        for (j = i + 1; j < patientCount; ++j) {
            if (patientmergencyLevel[order[j]] > patientmergencyLevel[order[i]]) {
                temporary = order[i];
                order[i] = order[j];
                order[j] = temporary;
            }
        }
    }

    printf("\nPriority Order (Critical -> Urgent -> Normal)\n");
    printf("%-12s %-25s %-12s %-20s \n", "Patient ID", "Name", "Urgency",
           "Specialty");
    for (i = 0; i < patientCount; ++i) {
        patientIndex = order[i];
        printf("PAT-%04d     %-25.25s %-12s %-20.20s\n", patientID[patientIndex],
        patientName[patientIndex], urgencyNames[patientmergencyLevel[patientIndex]],specialtyNames[patientSpecialtyID[patientIndex] - 1]);
    }
}


void displayBedOccupancyStatus() {
    int i, j, occupied;

    printf("\n====================================================\n");
    printf("                 BED OCCUPANCY STATUS\n");
    printf("          0 = Available | 1 = Occupied\n");
    printf("====================================================\n");

    for (i = 0; i < Wards_Count; ++i) {
        printf("\nWard ID   : %d\n", i + 1);
        printf("Ward Name : %s\n", WardsName[i]);
        printf("Beds      : ");

        for (j = 0; j < totalBedCapacity[i]; ++j) {
            printf("%d ", bedOccupancy[i][j]);
        }

        occupied = getOccupiedBedCount(i);

        printf("\nOccupied  : %d\n", occupied);
        printf("Available : %d\n", totalBedCapacity[i] - occupied);
        printf("Capacity  : %d\n", totalBedCapacity[i]);
        printf("----------------------------------------------------\n");
    }
}

