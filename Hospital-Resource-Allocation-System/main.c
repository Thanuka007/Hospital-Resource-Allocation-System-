#include <stdio.h>
#include <stdlib.h>
//function prototype
void printMenu();
void listSpecialties();
void listWardsData();
void patientRegistration();


int main(){
    int menuNum ;
    do{
        printMenu();
        printf("Enter an option :");
        scanf("%d",&menuNum);

        switch (menuNum){
            case 1: //Register a patient and generate a bill
                patientRegistration();
                break;
            case 2: //Display priority order
                break;
            case 3: //Display bed occupancy status
                break;
            case 4: //Display doctor specialties
                listSpecialties();
                break;
            case 5: //Display hospital wards
                listWardsData();
                break;
            case 6: //Generate performance report
                break;
            case 7:
                printf("Exit program ,GOODBYE");
                break;
            default:
                printf("Invalid number,(1-7)");
        }
    }while (menuNum != 7);
    return 0;



    }
