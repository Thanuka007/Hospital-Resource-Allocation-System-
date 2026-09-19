#include <stdio.h>
#include <stdlib.h>
//function prototype
void printMenu();
void listSpecialties();
void listWardsData();
void patientRegistration();
void displayPriorityOrder();
void displayBedOccupancyStatus();
void generatePerformanceReport();
void clearscreen();
void loadBedStatus();
void saveBedStatus();
void displaySavedPatientRecords();


int main(){
    int menuNum ;
    loadBedStatus();
    do{
        printMenu();
        do {
            printf("Enter a option (1 to 8) : ");

            if (scanf("%d",&menuNum)!= 1){
                printf("Invalid input.Please enter a number.\n");
                while (getchar()!= '\n');
                menuNum =0 ;
            }
        }while (menuNum < 1 || menuNum >8);


        switch (menuNum){
            case 1: //Register a patient and generate a bill
                clearscreen();
                patientRegistration();
                break;
            case 2: //Display priority order
                clearscreen();
                displayPriorityOrder();
                break;
            case 3: //Display bed occupancy status
                clearscreen();
                displayBedOccupancyStatus();
                break;
            case 4: //Display doctor specialties
                clearscreen();
                listSpecialties();
                break;
            case 5: //Display hospital wards
                clearscreen();
                listWardsData();
                break;
            case 6: //Generate performance report
                clearscreen();
                generatePerformanceReport();
                break;
            case 7:
                clearscreen();
                displaySavedPatientRecords();
                break;
            case 8:
                clearscreen();
                saveBedStatus();
                printf("Bed status saved. Exit program, GOODBYE");
                break;
            default:
                printf("Invalid number,(1-8)");
        }
    }while (menuNum != 8);
    return 0;



    }
