#include <stdio.h>

#define Specialty_Count 4
#define MAX_Patients 100
#define Wards_Count 4
#define MAX_Beds 20

const char specialtyNames[Specialty_Count][30] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};

const int specialtyID [Specialty_Count] = {1,2,3,4};
const double baseConsultationFee [Specialty_Count] = {1500.00,2500.00,4500.00,5000.00};
const int consultationTimePerPatient [Specialty_Count]= {15,20,30,30};
const int dailyPatientCap [Specialty_Count] = {30,20,12,10};

const char WardsName [Wards_Count][50] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU (Intensive Care Unit)"};

const int wardID [Wards_Count] = {1,2,3,4};
const double dailyBedRatePerLKRDay [Wards_Count] = {3000.00,6000.00,12000.00,25000.00};
const int totalBedCapacity [Wards_Count] = {20,10,10,05};

char patientName [MAX_Patients][50];
int patientAge [MAX_Patients]={0};
int patientmergencyLevel[MAX_Patients]={0};
int patientSpecialtyID [MAX_Patients]={0};
int patientWardID [MAX_Patients]={0};
int patientAssignedBed[MAX_Patients] = {0};
int patientDaysAdmitted [MAX_Patients]={0};
int patientestimatedWaitingTime [MAX_Patients]={0};
double patientEmergencySurcharge [MAX_Patients]={0};
double patienttotalWardStayCost [MAX_Patients]={0};
double patientGrossTotalBill [MAX_Patients]={0};
double patientAgeSubsidyDiscount [MAX_Patients]={0};
double patientFinalAmountPayable [MAX_Patients]={0};
int specialtyQueueCount[Specialty_Count] = {0, 0, 0, 0};
int patientID[MAX_Patients] = {0};
double patientBaseConsultationFee[MAX_Patients] = {0};
int bedOccupancy [4][20] = {0};
int patientCount =0;



void saveBedStatus() {
    FILE *file;
    int ward;
    int bed;

    file = fopen("beds_status.txt", "w");

    if (file == NULL) {
        printf("Error: Could not save bed status.\n");
        return;
    }

    for (ward = 0; ward < Wards_Count; ward++) {
        for (bed = 0; bed < MAX_Beds; bed++) {
            fprintf(file, "%d ", bedOccupancy[ward][bed]);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void loadBedStatus() {
    FILE *file;
    int ward;
    int bed;

    file = fopen("beds_status.txt", "r");

    if (file == NULL) {
        return;
    }

    for (ward = 0; ward < Wards_Count; ward++) {
        for (bed = 0; bed < MAX_Beds; bed++) {
            if (fscanf(file, "%d", &bedOccupancy[ward][bed]) != 1) {
                bedOccupancy[ward][bed] = 0;
            }
        }
    }

    fclose(file);
}

void savePatientRecord(int patientIndex) {
    FILE *file;
    const char *wardName;

    file = fopen("patient_records.txt", "a");

    if (file == NULL) {
        printf("Error: Could not save patient record.\n");
        return;
    }

    if (patientWardID[patientIndex] == 0) {
        wardName = "Not Admitted / OPD";
    } else {
        wardName = WardsName[patientWardID[patientIndex] - 1];
    }

    fprintf(file,
        "\n============================================================\n"
        "              SMART HOSPITAL PATIENT RECORD\n"
        "============================================================\n"
        "Patient ID              : PAT-%04d\n"
        "Patient Name            : %s\n"
        "Age                     : %d Years\n"
        "Emergency Level         : %d\n"
        "Specialty               : %s\n"
        "Ward                    : %s\n"
        "Bed Number              : %d\n"
        "Days Admitted           : %d\n"
        "------------------------------------------------------------\n"
        "Base Consultation Fee   : LKR %.2f\n"
        "Emergency Surcharge     : LKR %.2f\n"
        "Ward Stay Cost          : LKR %.2f\n"
        "------------------------------------------------------------\n"
        "Gross Total Bill        : LKR %.2f\n"
        "Age Subsidy Discount    : LKR %.2f\n"
        "Final Amount Payable    : LKR %.2f\n"
        "============================================================\n",
        patientID[patientIndex],
        patientName[patientIndex],
        patientAge[patientIndex],
        patientmergencyLevel[patientIndex],
        specialtyNames[patientSpecialtyID[patientIndex] - 1],
        wardName,
        patientAssignedBed[patientIndex],
        patientDaysAdmitted[patientIndex],
        patientBaseConsultationFee[patientIndex],
        patientEmergencySurcharge[patientIndex],
        patienttotalWardStayCost[patientIndex],
        patientGrossTotalBill[patientIndex],
        patientAgeSubsidyDiscount[patientIndex],
        patientFinalAmountPayable[patientIndex]
    );

    fclose(file);
}

void displaySavedPatientRecords() {
    FILE *file;
    int character;

    file = fopen("patient_records.txt", "r");

    if (file == NULL) {
        printf("No saved patient records found.\n");
        return;
    }

    printf("\n========== SAVED PATIENT RECORDS ==========\n");

    while ((character = fgetc(file)) != EOF) {
        putchar(character);
    }

    fclose(file);
}
