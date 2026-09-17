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


