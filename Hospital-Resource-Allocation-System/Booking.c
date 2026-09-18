#include <stdio.h>

#define Specialty_Count 4
#define MAX_Patients 100
#define Wards_Count 4
#define MAX_Beds 20

extern char patientName [MAX_Patients][50];
extern int paientAge [MAX_Patients];
extern int paientmergencyLevel[MAX_Patients];
extern int paientSpecialtyID [MAX_Patients];
extern int paientWardID [MAX_Patients];
extern int paientDaysAdmitted [MAX_Patients];
extern int paientestimatedWaitingTime [MAX_Patients];
extern double paientEmergencySurcharge [MAX_Patients];
extern double paienttotalWardStayCost [MAX_Patients];
extern double paientGrossTotalBill [MAX_Patients];
extern double paientAgeSubsidyDiscount [MAX_Patients];
extern double paientFinalAmountPayable [MAX_Patients];
extern int paientCount;
extern int specialtyQueueCount[Specialty_Count];
extern const int dailyPatientCap [Specialty_Count];
extern const int consultationTimePerPatient [Specialty_Count];
extern int paientID[MAX_Patients];
extern double paientBaseConsultationFee[MAX_Patients];
extern const double baseConsultationFee [Specialty_Count];
extern const double dailyBedRatePerLKRDay [Wards_Count];

void listSpecialties();

void patientRegistration (){
    int choice,specialtyIndex,wardIndex;
    if (paientCount >= MAX_Patients) {
        printf("Patient storage is full.\n");
        return;
    }
    printf("Enter patient name :");
    scanf("%s",patientName [paientCount]);
    printf("Enter patient Age :");
    scanf("%d",&paientAge [paientCount]);
    printf("Enter Emergency / Triage Level (1 = Normal, 2 = Urgent, 3 = Critical) :");
    scanf("%d",&paientmergencyLevel[paientCount]);

    printf("===========================================================\n");
    listSpecialties();
        do {
        printf("Enter Specialty ID (1 to 4): ");
        scanf("%d", &paientSpecialtyID[paientCount]);
        specialtyIndex = paientSpecialtyID[paientCount] - 1;
        if (specialtyIndex >= 0 && specialtyIndex < Specialty_Count &&
            specialtyQueueCount[specialtyIndex] >= dailyPatientCap[specialtyIndex]) {
            printf("This specialty has reached its daily patient cap.\n");
            paientSpecialtyID[paientCount] = 0;
        }
    } while (paientSpecialtyID[paientCount] < 1 || paientSpecialtyID[paientCount] > Specialty_Count);


    printf("Enter Specialty ID (1 to 4):");
    scanf("%d",&paientSpecialtyID [paientCount]);
    printf("Is Admitted to Ward? (1 = Yes, 0 = No):");
    scanf("%d",&choice);

    if (choice==1){
        printf("Input Ward ID (1 to 4):");
        scanf("%d",&paientWardID[paientCount]);
        printf("Days Admitted :");
        scanf("%d",&paientDaysAdmitted[paientCount]);
    }else {
        paientDaysAdmitted [paientCount]=0;
    }


    specialtyIndex = paientSpecialtyID[paientCount] - 1;
    /* Waiting time is calculated BEFORE this patient is added to the queue. */
    paientestimatedWaitingTime[paientCount] = specialtyQueueCount[specialtyIndex] *consultationTimePerPatient[specialtyIndex];
    specialtyQueueCount[specialtyIndex]++;

    paientID[paientCount] = 1001 + paientCount;
    paientBaseConsultationFee[paientCount] = baseConsultationFee[specialtyIndex];

    if (paientmergencyLevel[paientCount]=1){
        paientEmergencySurcharge [paientCount]=baseConsultationFee[paientCount] *0.20;
    }
    else {
        paientEmergencySurcharge [paientCount]=baseConsultationFee[paientCount] *0.50;
    }

    if (choice==1){
        wardIndex = paientWardID[paientCount] - 1;
        paienttotalWardStayCost [paientCount]= paientDaysAdmitted[paientCount]*dailyBedRatePerLKRDay [Wards_Count];
    }else {
       paienttotalWardStayCost[paientCount] = 0.0 ;
    }

    paientGrossTotalBill [paientCount] = paientBaseConsultationFee[paientCount]+paientEmergencySurcharge [paientCount]+paienttotalWardStayCost [paientCount];

    if (paientAge [paientCount]<5 || paientAge [paientCount]>65){
        paientAgeSubsidyDiscount [paientCount] = paientGrossTotalBill [paientCount]*0.15;
    }
    else {
        paientAgeSubsidyDiscount [paientCount] =0;
    }

    paientFinalAmountPayable [paientCount] = paientGrossTotalBill [paientCount]-paientAgeSubsidyDiscount [paientCount];

    paientCount++;


}
