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

int main(){
    int menuNum ;
    do{
        printMenu();
        printf("Enter an option :");
        scanf("%d",&menuNum);

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
                printf("Exit program ,GOODBYE");
                break;
            default:
                printf("Invalid number,(1-7)");
        }
    }while (menuNum != 7);
    return 0;



    }
