#include <stdio.h>
#include <stdlib.h>
#include "HashTableTypes.h"
#include "HashTableInterface.h"
#include "menuInterface.h"



int main(void){

    int choice;
    Table T;
    T=makeTable(T);

    while(1){
        menuInterface();

        printf("Input your choice:");
        scanf("%d",&choice);



        switch(choice){

        case 1 :
            menuManualInsert(&T);
            break;
        case 2 :
            menuFileInsert(&T);
            break;
        case 3:
            menuCustomSearch(T);
            break;
        case 4:
            menuSearchAll(T);
            break;
        case 5:
            printTable(T);
            break;
        case 6:
            printf("Bye bye...\n");
            return 0;
            break;
        default : printf("Wrong input.Try again...");


    }
    printf("\n\n\n\n");


}


    return 0;
}
